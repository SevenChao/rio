// This file is part of RIO - Radar Inertial Odometry and Radar ego velocity estimation.
// Copyright (C) 2021  Christopher Doer <christopher.doer@kit.edu>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <numeric>

#include <angles/angles.h>

#include <rio_utils/data_types.h>
#include <rio_utils/ros_helper.h>
#include <rio_utils/math_helper.h>

#include <ekf_yrio/ekf_yrio_filter.h>

#include <ekf_yrio/data_types.h>

#include <ekf_yrio/EkfYRioConfig.h>

namespace rio
{
/**
 * @brief The YawAidingManhattanWorld class implements yaw aiding based on Manhattan world assumptions
 */
class YawAidingManhattanWorld
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  /**
   * @brief YawAidingManhattanWorld constructor
   */
  YawAidingManhattanWorld(ros::NodeHandle& nh);

  /**
   * @brief Update function which handles initilization and update
   * @param radar_scan_msg             radar scan
   * @param radar_filter_state         relating radar filter state
   * @returns true if successful
   */
  bool update(const sensor_msgs::PointCloud2& radar_scan_msg,
              const RadarCloneState& radar_filter_state,
              Real& yaw_m,
              sensor_msgs::PointCloud2& yaw_inlier);

  /**
   * @brief Reconfigure callback
   * @param config   has to contain the fields of EkfYRioConfig
   */
  template <class ConfigContainingEkfYRioConfig>
  void configure(ConfigContainingEkfYRioConfig& config);

  /**
   * @brief Returns the Manhattan world angle
   */
  Real getManhattanAngle() const { return gamma_manhattan_; }

protected:
  /**
   * @brief Tries to initialize the Manhattan world angle
   * @param radar_scan_msg      radar scan
   * @param radar_filter_state  relating radar filter state
   * @returns true if successful
   */
  bool init(const sensor_msgs::PointCloud2& radar_scan_msg, const RadarCloneState& radar_filter_state);

  /**
   * @brief Does the preprocessing step of the given radar scan
   * @param radar_scan_msg        radar scan
   * @param radar_state           corresponding radar clone state
   * @param[out] detections_filtered   filtered detections
   * @returns true if detections_filtered valid
   */
  bool getFilteredDetections(const sensor_msgs::PointCloud2& radar_scan_msg,
                             const RadarCloneState& radar_state,
                             RadarDetections& detections_filtered);

  /**
   * @brief Helper which convert RadarDetections into a PointCloud2 message
   * @param detections    RadarDetections
   * @param header        header of resulting point cloud
   * @param[out] pcl_msg  resulting point cloud message
   * @param use_p_r       if true p_r is used instead of p_n
   */
  void convertToPcl(const RadarDetections& detections,
                    const std_msgs::Header& header,
                    sensor_msgs::PointCloud2& pcl_msg,
                    const bool use_p_r = true) const;

  /**
   * @brief Calculates the candidate histogram with a bin size 1 deg
   */
  Vector360 getCandidateHistogram(const Candidates& candidates);

  /**
   * @brief Calculates the convolution kernel
   */
  Vector getConvKernel();

  const std::string kPrefix = "[yaw_aiding]: ";

  ekf_yrio::EkfYRioConfig config_;

  Real gamma_manhattan_ = 0.;
  bool initialized_     = false;
  Candidates candidates_;
  uint N_init_scans_ = 0;

  std::string frame_id_;

  ros::Publisher pub_filtered_;
  ros::Publisher pub_init_;
};

template <class Cfg>
void YawAidingManhattanWorld::configure(Cfg& config)
{
  config_.yaw_aiding_max_dist          = config.yaw_aiding_max_dist;
  config_.yaw_aiding_ele_thresh_deg    = config.yaw_aiding_ele_thresh_deg;
  config_.yaw_aiding_min_snr_detection = config.yaw_aiding_min_snr_detection;
  config_.yaw_aiding_min_v_xy          = config.yaw_aiding_min_v_xy;

  config_.yaw_aiding_N_init         = config.yaw_aiding_N_init;
  config_.yaw_aiding_min_N_peak     = config.yaw_aiding_min_N_peak;
  config_.yaw_aiding_N_gaussian     = config.yaw_aiding_N_gaussian;
  config_.yaw_aiding_gaussian_sigma = config.yaw_aiding_gaussian_sigma;

  config_.yaw_aiding_init_inlier_thresh_deg = config.yaw_aiding_init_inlier_thresh_deg;
  config_.yaw_aiding_yaw_inlier_thresh_deg  = config.yaw_aiding_yaw_inlier_thresh_deg;

  frame_id_ = config.frame_id;
}

}  // namespace rio

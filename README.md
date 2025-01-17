# RIO - Radar Inertial Odometry and Radar based Ego Velocity Estimation
Navigation in GNSS denied and visually degraded environments is still very challenging. 
Approaches based on visual sensors tend to fail in conditions such as darkness, direct sunlight, fog or smoke.
Therefore, we are using mmWave FMCW radar and inertial sensor data as these are not affected by such conditions.

***Highlights:***
- Robust and accurate navigation even in Degraded Visual and GNSS denied Environments
- Super fast: run-times ~90x faster than realtime on an Intel NUC i7 and ~10x on an Intel UpCore embedded computer
- Demonstrated for online navigation of drones even in confined indoor environments

## News
- 06/2021: The radar inertial datasets with pseudo ground truth used in our [Yaw aided Radar Inertial Odometry](https://christopherdoer.github.io/publication/2021_05_ICINS2021) paper are released: [radar_inertial_datasets_icins_2021](https://christopherdoer.github.io/datasets/icins_2021_radar_inertial_odometry). 
  Both ekf_rio and ekf_yrio can be evaluated on the whole dataset with a single [script](ekf_yrio/python/icins_2021_evaluation.py).
- 05/2021: Initial release of RIO - Radar Inertial Odometry and Radar based ego velocity estimation.

## Introduction
RIO is a toolbox for EKF-based Radar Inertial Odometry and Radar based ego velocity estimation.
RIO features the following packages:
- [radar_ego_velocity_estimation](radar_ego_velocity_estimation): Instantaneous 3D ego velocity estimation based on a single radar scan
- [ekf_rio](ekf_rio): An EKF-based Radar Inertial Odometry Pipeline with online calibration of the radar sensor extrinsics
- [ekf_yrio](ekf_yrio): An extension of ekf_rio featuring yaw aiding based on Manhattan world assumptions 

Checkout the README files of the individual packages for more details.

## Demos

### Autonomous Indoor Drone Flight using Yaw aided Radar Inertial Odometry ([ekf_yrio](./ekf_yrio))   
[![Autonomous Indoor Drone Flights using Yaw aided Radar Inertial Odometry](http://img.youtube.com/vi/KhWPqMC6gSE/0.jpg)](http://www.youtube.com/watch?v=KhWPqMC6gSE "Autonomous Indoor Drone Flights using Yaw aided Radar Inertial Odometry")

### Indoor Demo and Evaluation of Yaw aided Radar Inertial Odometry ([ekf_yrio](./ekf_yrio))   
[![Autonomous UAV Flights using Radar Inertial Odometry](http://img.youtube.com/vi/EIcBMo1sM_g/0.jpg)](http://www.youtube.com/watch?v=EIcBMo1sM_g "Autonomous UAV Flights using Radar Inertial Odometry")

### Autonomous UAV Flights using Radar Inertial Odometry ([ekf_rio](./ekf_rio))
[![Autonomous UAV Flights using Radar Inertial Odometry](http://img.youtube.com/vi/8DofG1iXHAE/0.jpg)](http://www.youtube.com/watch?v=8DofG1iXHAE "Autonomous UAV Flights using Radar Inertial Odometry")


## References

If you use our implementation for your academic research, please cite the related paper:

***ekf_yrio:***
~~~[bibtex]
@INPROCEEDINGS{DoerICINS2021,
  author={Doer, Christopher and Trommer, Gert F.},
  booktitle={2021 28th Saint Petersburg International Conference on Integrated Navigation Systems (ICINS)}, 
  title={Yaw aided Radar Inertial Odometry uisng Manhattan World Assumptions}, 
  year={2021},
  pages={1-10}
~~~

***ekf_rio and radar_ego_velocity_estimation:***
~~~[bibtex]
@INPROCEEDINGS{DoerENC2020,
  author={Doer, Christopher and Trommer, Gert F.},
  booktitle={2020 European Navigation Conference (ENC)}, 
  title={Radar Inertial Odometry with Online Calibration}, 
  year={2020},
  pages={1-10},
  doi={10.23919/ENC48637.2020.9317343}}
~~~
~~~[bibtex]
@INPROCEEDINGS{DoerMFI2020,
  author={Doer, Christopher and Trommer, Gert F.},
  booktitle={2020 IEEE International Conference on Multisensor Fusion and Integration for Intelligent Systems (MFI)}, 
  title={An EKF Based Approach to Radar Inertial Odometry}, 
  year={2020},
  pages={152-159},
  doi={10.1109/MFI49285.2020.9235254}}
~~~


## Getting Started
Our implementation depends on:
- Ubuntu 16.04 and ROS Kinetic
- [catkin_simple](https://github.com/catkin/catkin_simple.git)  
- [catkin_tools](https://catkin-tools.readthedocs.io/en/latest/) (for convenience)
- [rpg_trajectory_evaluation](https://github.com/christopherdoer/rpg_trajectory_evaluation) (optional, for comprehensive evaluation)
  - sudo apt-get install texlive-latex-extra texlive-fonts-recommended dvipng cm-super
  - pip2 install -U PyYAML colorama ruamel.yaml==0.15.0 

**Build in Release is highly recommended**:
~~~[shell]
catkin build --cmake-args -DCMAKE_BUILD_TYPE=Release
~~~

We provide some demo datasets which can be run using the demo launch files of each package. 
Check out the ***Getting Started*** section of the READMEs in the individual packages for more details. 


## License
The source code is released under the [GPLv3](http://www.gnu.org/licenses/) license.

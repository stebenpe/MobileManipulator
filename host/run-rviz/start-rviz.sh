#!/bin/bash
export DISPLAY=:10

source /opt/ros/humble/setup.bash

source /home/steven/Desktop/docker/ubuntu_minimal_ros2_humble/Data/ros2_ws/Omron_AMR_ROS2/install/setup.bash

ros2 launch amr_visualisation display.launch.py
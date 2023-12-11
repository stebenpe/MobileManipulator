ARG ROS2_version=humble     #Humble, foxy or iron
ARG ROS2_type=desktop       #desktop, core or base
ARG ROS2_workspace=~/ros2_ws

ARG L4T_major=35
ARG L4T_minor=4
ARG L4T_patch=1

ARG ZEDsdk_version=4.0
ARG ZEDsdk_patch=7

FROM dustynv/ros:${ROS2_version}-${ROS2_type}-l4t-r${L4T_major}.${L4T_minor}.${L4T_patch}

RUN mkdir ${ROS2_workspace}

# install ros2 library's
RUN apt install -y ros-${ROS2_version}-moveit

# install the ZED sdk
RUN mkdir ZED
RUN cd ZED
RUN wget https://download.stereolabs.com/zedsdk/${ZEDsdk_version}/l4t${L4T_major}.${L4T_minor}/jetsons
RUN chmod +x ZED_SDK_Tegra_L4T35.4_v4.0.7.zstd.run
RUN ./chmod +x ZED_SDK_Tegra_L4T${L4T_major}.${L4T_minor}_v${ZEDsdk_version}.${ZEDsdk_patch}.zstd.run -- silent

# install ros2_zed_wrapper
RUN cd ${ROS2_workspace}
RUN mkdir src
RUN cd src
RUN git clone  --recursive https://github.com/stereolabs/zed-ros2-wrapper.git
RUN cd ..
RUN rosdep install --from-paths src --ignore-src -r -y
RUN colcon build --symlink-install --cmake-args=-DCMAKE_BUILD_TYPE=Release --parallel-workers $(nproc)


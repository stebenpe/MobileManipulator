FROM osrf/ros:iron-desktop
# install rtabmap packages
ARG CACHE_DATE=2016-01-01
RUN apt-get update && apt-get install -y \
    ros-iron-rtabmap \
    ros-iron-rtabmap-ros \
    && rm -rf /var/lib/apt/lists/

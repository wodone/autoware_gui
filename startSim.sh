#!/bin/sh
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
ros2 launch turtlebot3_navigation2 navigation2.launch.py map:=/home/ros2/map/house.yaml

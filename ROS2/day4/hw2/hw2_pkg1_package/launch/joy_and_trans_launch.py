#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription({
        Node(
            package='hw2_pkg1',
            executable='hw2_pkg1_node',
            name='hw2_pkg1',
            output='screen'
        ),
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node'
        ),
    })
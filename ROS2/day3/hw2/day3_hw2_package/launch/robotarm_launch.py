import os

from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():  
    param_dir = LaunchConfiguration(
        'param_dir',
        default=os.path.join(
            get_package_share_directory('day3_hw2'),
            'param',
            'robotarm_config.yaml'
        )
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'param_dir',
            default_value=param_dir,
            description='Full path of parameter file'),

        Node(
            package='day3_hw2',
            executable='day3_hw2_node',
            parameters=[param_dir],
            output='screen')
    ])
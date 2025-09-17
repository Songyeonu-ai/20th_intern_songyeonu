from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='hw2_pkg2',
            executable='hw2_node',
            name='broadcaster1',
            parameters=[
                {'movingframe': 'odom'}
            ]
        ),
    ])
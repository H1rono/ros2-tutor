from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="cpp_parameters",
            executable="param",
            name="custom_param_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"my_parameter": "ROS2"}
            ]
        )
    ])

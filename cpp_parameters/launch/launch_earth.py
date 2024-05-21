from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    container = ComposableNodeContainer(
        name="my_container",
        namespace="",
        package="rclcpp_components",
        executable="component_container",
        composable_node_descriptions=[ComposableNode(
            package="cpp_parameters",
            plugin="param::Parameters",
            name="param",
            parameters=[
                {"my_parameter": "earth"}
            ]
        )]
    )
    return LaunchDescription([container])

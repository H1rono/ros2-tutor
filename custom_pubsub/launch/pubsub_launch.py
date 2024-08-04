from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    num_pub = ComposableNode(
        package="custom_pubsub",
        plugin="num_pub::NumPublisher",
        name="numpub",
        parameters=[],
    )
    num_sub = ComposableNode(
        package="custom_pubsub",
        plugin="num_sub::NumSubscriber",
        name="numsub",
        parameters=[],
    )
    container = ComposableNodeContainer(
        name="custom_pubsub_container",
        namespace="num",
        package="rclcpp_components",
        executable="component_container",
        composable_node_descriptions=[num_pub, num_sub],
    )
    return LaunchDescription([container])

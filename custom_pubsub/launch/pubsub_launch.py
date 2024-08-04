from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    initial_count_arg = DeclareLaunchArgument("initial_count", default_value="0")
    num_pub = ComposableNode(
        package="custom_pubsub",
        plugin="num_pub::NumPublisher",
        name="numpub",
        parameters=[
            {"initial_count": ParameterValue(LaunchConfiguration("initial_count"))}
        ],
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
    return LaunchDescription([initial_count_arg, container])

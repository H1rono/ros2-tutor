#include <functional>

#include "rclcpp_components/register_node_macro.hpp"

#include "num_pubsub/num_subscriber.hpp"

void num_sub::NumSubscriber::topic_callback(const tutorial_interfaces::msg::Num& msg) {
    RCLCPP_INFO_STREAM(this->get_logger(), "subscribe: '" << msg.num << "'");
}

num_sub::NumSubscriber::NumSubscriber(const rclcpp::NodeOptions& options) :
    rclcpp::Node("num_subscriber", options),
    subscription() {
    using std::placeholders::_1;
    this->subscription = this->create_subscription<tutorial_interfaces::msg::Num>(
        "num", 10, std::bind(&num_sub::NumSubscriber::topic_callback, this, _1)
    );
}

RCLCPP_COMPONENTS_REGISTER_NODE(num_sub::NumSubscriber)

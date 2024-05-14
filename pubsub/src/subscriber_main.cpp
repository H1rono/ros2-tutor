#include <functional>
#include <string>

#include "pubsub/subscriber.hpp"

void sub::Subscriber::topic_callback(const std_msgs::msg::String &msg) {
    RCLCPP_INFO(this->get_logger(), "hear %s", msg.data.c_str());
}

sub::Subscriber::Subscriber():
    rclcpp::Node("subscriber"),
    subscription()
{
    using std::placeholders::_1;
    auto callback = std::bind(&::sub::Subscriber::topic_callback, this, _1);
    subscription = this->create_subscription<std_msgs::msg::String>("chatter", 10, callback);
}

#pragma once

#include <memory>

#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

namespace sub {

class Subscriber : public rclcpp::Node {
private:
    std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> subscription;
    void topic_callback(const std_msgs::msg::String& msg);

public:
    Subscriber();
};

}

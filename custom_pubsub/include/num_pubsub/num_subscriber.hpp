#pragma once

#include "tutorial_interfaces/msg/num.hpp"
#include "rclcpp/rclcpp.hpp"

namespace num_sub {

class NumSubscriber : public rclcpp::Node {
private:
    rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription;

    void topic_callback(const tutorial_interfaces::msg::Num&);

public:
    NumSubscriber();
};

}

#pragma once

#include <memory>

#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

namespace pub {

class Publisher : public rclcpp::Node {
private:
    rclcpp::TimerBase::SharedPtr                        timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    std::size_t                                         count = 0;

    void timer_callback();

public:
    Publisher();
};

}

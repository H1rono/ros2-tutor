#pragma once

#include "tutorial_interfaces/msg/num.hpp"
#include "rclcpp/rclcpp.hpp"

namespace num_pub {

class NumPublisher : public rclcpp::Node {
private:
    rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr                                timer;
    std::size_t                                                 count;
    void                                                        timer_callback();

public:
    NumPublisher(const rclcpp::NodeOptions& options = rclcpp::NodeOptions{});
};

} // namespace num_pub

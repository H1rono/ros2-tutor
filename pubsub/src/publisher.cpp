#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "pubsub/publisher.hpp"

void pub::Publisher::timer_callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, ROS2! " + std::to_string(this->count);
    this->count += 1;
    RCLCPP_INFO(this->get_logger(), "Say: '%s'", message.data.c_str());
    this->publisher->publish(message);
}

pub::Publisher::Publisher() : rclcpp::Node("publisher") {
    using namespace std::chrono_literals;
    this->publisher = this->create_publisher<std_msgs::msg::String>("chatter", 10);
    this->timer     = this->create_wall_timer(
        800ms, std::bind(&pub::Publisher::timer_callback, this)
    );
}

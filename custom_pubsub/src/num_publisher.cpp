#include <chrono>
#include <functional>
#include <string>

#include "rclcpp_components/register_node_macro.hpp"

#include "num_pubsub/num_publisher.hpp"

num_pub::NumPublisher::NumPublisher(const rclcpp::NodeOptions& options) :
    rclcpp::Node("num_publisher", options),
    publisher(),
    timer(),
    count(0) {
    using namespace std::chrono_literals;
    constexpr char parameter_name[] = "initial_count";

    this->declare_parameter(parameter_name, 0);
    this->publisher = this->create_publisher<tutorial_interfaces::msg::Num>("num", 10);
    this->timer
        = this->create_wall_timer(500ms, std::bind(&NumPublisher::timer_callback, this));
    this->count = static_cast<std::size_t>(this->get_parameter(parameter_name).as_int());
}

void num_pub::NumPublisher::timer_callback() {
    auto message = tutorial_interfaces::msg::Num();
    message.num  = this->count;
    this->count += 1;
    RCLCPP_INFO_STREAM(this->get_logger(), "publishing: '" << message.num << "'");
    this->publisher->publish(message);
}

RCLCPP_COMPONENTS_REGISTER_NODE(num_pub::NumPublisher)

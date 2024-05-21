#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp_components/register_node_macro.hpp"

#include "cpp_parameters/parameters.hpp"

void param::Parameters::timer_callback() {
    std::string my_param = this->get_parameter("my_parameter").as_string();
    RCLCPP_INFO_STREAM(this->get_logger(), "Hello, " << my_param << "!");
}

param::Parameters::Parameters(const rclcpp::NodeOptions& options) :
    rclcpp::Node("parameter", options),
    timer() {
    using namespace std::chrono_literals;
    this->declare_parameter("my_parameter", "world");
    this->event_handler = std::make_shared<rclcpp::ParameterEventHandler>(this);
    auto callback       = [this](const rclcpp::Parameter& p) {
        RCLCPP_INFO_STREAM(
            this->get_logger(),
            "callback: Received an update to parameter \""
                << p.get_name() << "\" of type " << p.get_type_name() << ": \""
                << p.as_string() << "\""
        );
    };
    this->callback_handle
        = this->event_handler->add_parameter_callback("my_parameter", callback);
    this->timer
        = this->create_wall_timer(1s, std::bind(&Parameters::timer_callback, this));
}

RCLCPP_COMPONENTS_REGISTER_NODE(param::Parameters)

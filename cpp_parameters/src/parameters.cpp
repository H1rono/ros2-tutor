#include <chrono>
#include <functional>
#include <string>

#include "cpp_parameters/parameters.hpp"

void param::Parameters::timer_callback() {
    std::string my_param = this->get_parameter("my_parameter").as_string();
    RCLCPP_INFO_STREAM(this->get_logger(), "Hello, " << my_param << "!");
    std::vector<rclcpp::Parameter> all_new_parameters{
        rclcpp::Parameter("my_parameter", "world")
    };
    this->set_parameters(all_new_parameters);
}

param::Parameters::Parameters() : rclcpp::Node("parameter"), timer() {
    using namespace std::chrono_literals;
    this->declare_parameter("my_parameter", "world");
    this->timer
        = this->create_wall_timer(1s, std::bind(&Parameters::timer_callback, this));
}

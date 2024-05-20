#include <memory>

#include "cpp_parameters/parameters.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<param::Parameters>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

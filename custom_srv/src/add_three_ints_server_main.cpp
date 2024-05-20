#include <memory>

#include "custom_srv/add_three_ints_server.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<add_three_ints::Server>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

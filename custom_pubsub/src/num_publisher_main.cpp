#include <memory>

#include "num_pubsub/num_publisher.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<num_pub::NumPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

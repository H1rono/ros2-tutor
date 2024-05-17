#include <memory>

#include "pubsub/publisher.hpp"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<pub::Publisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

#include <memory>

#include "num_pubsub/num_subscriber.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<num_sub::NumSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

#include <chrono>
#include <memory>

#include "custom_srv/add_three_ints_client.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    using namespace std::chrono_literals;
    using add_three_ints::Client;
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Client>();
    if (argc != 4) {
        RCLCPP_INFO(node->get_logger(), "usage: client X Y Z");
        return 1;
    }

    while (!node->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_INFO(node->get_logger(), "Interrupted while waiting for service");
            return 0;
        }
        RCLCPP_INFO(node->get_logger(), "service not available, waiting again");
    }

    auto request    = std::make_shared<Client::Service::Request>();
    request->first  = std::stoi(argv[1]);
    request->second = std::stoi(argv[2]);
    request->third  = std::stoi(argv[3]);
    auto result     = node->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node, result)
        == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO_STREAM(node->get_logger(), "Sum: " << result.get()->sum);
    } else {
        RCLCPP_INFO_STREAM(
            node->get_logger(), "Failed to call service and add_three_ints"
        );
    }
    rclcpp::shutdown();
    return 0;
}

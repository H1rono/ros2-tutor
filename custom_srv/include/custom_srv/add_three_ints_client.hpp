#include <chrono>
#include <cstdint>

#include "tutorial_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

namespace add_three_ints {

class Client : public rclcpp::Node {
public:
    using Service = tutorial_interfaces::srv::AddThreeInts;

private:
    rclcpp::Client<Service>::SharedPtr client;

public:
    Client();

    bool wait_for_service(const std::chrono::duration<std::int64_t>& delay);

    rclcpp::Client<Service>::FutureAndRequestId
    async_send_request(Service::Request::SharedPtr request);
};

}

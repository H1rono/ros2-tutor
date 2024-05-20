#include <functional>

#include "custom_srv/add_three_ints_server.hpp"

using add_three_ints::Server;

void Server::service_callback(
    const Service::Request::SharedPtr request, Service::Response::SharedPtr response
) {
    response->sum = request->first + request->second + request->third;
    RCLCPP_INFO_STREAM(
        this->get_logger(),
        "Incoming request: {first = " << request->first
                                      << ", second = " << request->second
                                      << ", third = " << request->third << "}"
    );
    RCLCPP_INFO_STREAM(
        this->get_logger(), "Sending back response: {sum = " << response->sum << "}"
    );
}

Server::Server() : rclcpp::Node("add_three_ints_server"), service() {
    using namespace std::placeholders;
    this->service = this->create_service<Service>(
        "add_three_ints", std::bind(&Server::service_callback, this, _1, _2)
    );
}

#include "custom_srv/add_three_ints_client.hpp"

using add_three_ints::Client;

Client::Client() : rclcpp::Node("add_three_ints_client"), client() {
    this->client = this->create_client<Client::Service>("add_three_ints");
}

bool Client::wait_for_service(const std::chrono::duration<std::int64_t>& delay) {
    return this->client->wait_for_service(delay);
}

rclcpp::Client<Client::Service>::FutureAndRequestId
Client::async_send_request(Service::Request::SharedPtr request) {
    return this->client->async_send_request(request);
}

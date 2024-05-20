#include "tutorial_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

namespace add_three_ints {

class Server : public rclcpp::Node {
private:
    using Service = tutorial_interfaces::srv::AddThreeInts;
    rclcpp::Service<Service>::SharedPtr service;

    void service_callback(
        const Service::Request::SharedPtr request, Service::Response::SharedPtr response
    );

public:
    Server();
};

}

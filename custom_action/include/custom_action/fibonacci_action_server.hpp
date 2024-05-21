#ifndef CUSTOM_ACTION_FIBONACCI_ACTION_SERVER_HPP
#define CUSTOM_ACTION_FIBONACCI_ACTION_SERVER_HPP

#include <memory>

#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "tutorial_interfaces/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"

namespace fibonacci {

class ActionServer : public rclcpp::Node {
public:
    using Fibonacci           = tutorial_interfaces::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

    explicit ActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

private:
    rclcpp_action::Server<Fibonacci>::SharedPtr action_server;

    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID& uuid, std::shared_ptr<const Fibonacci::Goal> goal
    );

    rclcpp_action::CancelResponse
    handle_cancel(const std::shared_ptr<GoalHandleFibonacci> goal_handle);

    void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle);

    void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle);
};

}

#endif // CUSTOM_ACTION_FIBONACCI_ACTION_SERVER_HPP

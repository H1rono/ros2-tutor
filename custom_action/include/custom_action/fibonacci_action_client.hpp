#ifndef CUSTOM_ACTION_FIBONACCI_ACTION_CLIENT_HPP
#define CUSTOM_ACTION_FIBONACCI_ACTION_CLIENT_HPP

#include <memory>

#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp/rclcpp.hpp"

#include "tutorial_interfaces/action/fibonacci.hpp"

namespace fibonacci {

class ActionClient : public rclcpp::Node {
public:
    using Fibonacci           = tutorial_interfaces::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

    explicit ActionClient(const rclcpp::NodeOptions& options);

    void send_goal();

private:
    rclcpp_action::Client<Fibonacci>::SharedPtr client;
    rclcpp::TimerBase::SharedPtr                timer;

    void goal_response_callback(const GoalHandleFibonacci::SharedPtr& goal_handle);

    void feedback_callback(
        GoalHandleFibonacci::SharedPtr,
        const std::shared_ptr<const Fibonacci::Feedback> feedback
    );

    void result_callback(const GoalHandleFibonacci::WrappedResult& result);
};

}

#endif // CUSTOM_ACTION_FIBONACCI_ACTION_CLIENT_HPP

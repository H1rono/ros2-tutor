#include <chrono>
#include <functional>
#include <future>
#include <sstream>
#include <string>

#include "rclcpp_components/register_node_macro.hpp"

#include "custom_action/fibonacci_action_client.hpp"

fibonacci::ActionClient::ActionClient(const rclcpp::NodeOptions& options) :
    rclcpp::Node("fibonacci_action_client", options) {
    using namespace std::chrono_literals;
    this->client = rclcpp_action::create_client<Fibonacci>(this, "fibonacci");
    this->timer
        = this->create_wall_timer(500ms, std::bind(&ActionClient::send_goal, this));
}

void fibonacci::ActionClient::send_goal() {
    using namespace std::placeholders;

    this->timer->cancel();

    if (!this->client->wait_for_action_server()) {
        RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
        rclcpp::shutdown();
    }

    auto goal_msg  = Fibonacci::Goal();
    goal_msg.order = 10;

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
    send_goal_options.goal_response_callback
        = std::bind(&ActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback
        = std::bind(&ActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback
        = std::bind(&ActionClient::result_callback, this, _1);
    this->client->async_send_goal(goal_msg, send_goal_options);
}

void fibonacci::ActionClient::
    goal_response_callback(const GoalHandleFibonacci::SharedPtr& goal_handle) {
    if (!goal_handle) {
        RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
        RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
}

void fibonacci::ActionClient::feedback_callback(
    GoalHandleFibonacci::SharedPtr,
    const std::shared_ptr<const Fibonacci::Feedback> feedback
) {
    std::stringstream ss;
    ss << "Next number in sequence received:";
    for (auto number : feedback->partial_sequence) {
        ss << " " << number;
    }
    RCLCPP_INFO_STREAM(this->get_logger(), ss.str());
}

void fibonacci::ActionClient::
    result_callback(const GoalHandleFibonacci::WrappedResult& result) {
    switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED: break;
    case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
    case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
    default: RCLCPP_ERROR(this->get_logger(), "Unknown result code"); return;
    }
    std::stringstream ss;
    ss << "Result received:";
    for (auto number : result.result->sequence) {
        ss << " " << number;
    }
    RCLCPP_INFO_STREAM(this->get_logger(), ss.str());
    rclcpp::shutdown();
}

RCLCPP_COMPONENTS_REGISTER_NODE(fibonacci::ActionClient)

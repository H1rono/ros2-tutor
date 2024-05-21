#include <functional>
#include <thread>

#include "rclcpp_components/register_node_macro.hpp"

#include "custom_action/fibonacci_action_server.hpp"

fibonacci::ActionServer::ActionServer(const rclcpp::NodeOptions& options) :
    rclcpp::Node("fibonacci_action_server", options),
    action_server() {
    using namespace std::placeholders;

    this->action_server = rclcpp_action::create_server<Fibonacci>(
        this,
        "fibonacci",
        std::bind(&fibonacci::ActionServer::handle_goal, this, _1, _2),
        std::bind(&fibonacci::ActionServer::handle_cancel, this, _1),
        std::bind(&fibonacci::ActionServer::handle_accepted, this, _1)
    );
}

rclcpp_action::GoalResponse fibonacci::ActionServer::handle_goal(
    const rclcpp_action::GoalUUID& _, std::shared_ptr<const Fibonacci::Goal> goal
) {
    RCLCPP_INFO_STREAM(
        this->get_logger(), "Received goal request with order " << goal->order
    );
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse
fibonacci::ActionServer::handle_cancel(const std::shared_ptr<GoalHandleFibonacci> _) {
    RCLCPP_INFO_STREAM(this->get_logger(), "Received request to cancel goal");
    return rclcpp_action::CancelResponse::ACCEPT;
}

void fibonacci::ActionServer::
    handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle) {
    using namespace std::placeholders;
    std::thread{ std::bind(&ActionServer::execute, this, _1), goal_handle }.detach();
}

void
fibonacci::ActionServer::execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate{ 1 };
    const auto   goal     = goal_handle->get_goal();
    auto         feedback = std::make_shared<Fibonacci::Feedback>();
    auto&        sequence = feedback->partial_sequence;
    sequence.push_back(0);
    sequence.push_back(1);
    auto result = std::make_shared<Fibonacci::Result>();
    for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
        // Check if there is a cancel request
        if (goal_handle->is_canceling()) {
            result->sequence = sequence;
            goal_handle->canceled(result);
            RCLCPP_INFO(this->get_logger(), "Goal canceled");
            return;
        }
        // Update sequence
        sequence.push_back(sequence[i] + sequence[i - 1]);
        // Publish feedback
        goal_handle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(), "Publish feedback");

        loop_rate.sleep();
    }

    // Check if goal is done
    if (rclcpp::ok()) {
        result->sequence = sequence;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
}

RCLCPP_COMPONENTS_REGISTER_NODE(fibonacci::ActionServer);

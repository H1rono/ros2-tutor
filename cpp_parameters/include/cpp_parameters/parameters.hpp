#include <memory>

#include "rclcpp/rclcpp.hpp"

namespace param {

class Parameters : public rclcpp::Node {
private:
    rclcpp::TimerBase::SharedPtr                     timer;
    std::shared_ptr<rclcpp::ParameterEventHandler>   event_handler;
    std::shared_ptr<rclcpp::ParameterCallbackHandle> callback_handle;

    void timer_callback();

public:
    explicit Parameters(const rclcpp::NodeOptions& options);
};

}

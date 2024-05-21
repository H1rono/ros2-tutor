#include "rclcpp/rclcpp.hpp"

namespace param {

    class Parameters : public rclcpp::Node {
    private:
        rclcpp::TimerBase::SharedPtr timer;

        void timer_callback();

    public:
        Parameters(const rclcpp::NodeOptions &options);
    };

}

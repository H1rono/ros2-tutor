import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class Subscriber(Node):
    def __init__(self):
        super().__init__("subscriber_py")
        self._subscription = self.create_subscription(
            String,
            "chatter",
            self._topic_callback,
            10
        )

    def _topic_callback(self, msg):
        self.get_logger().info(f"hear: {msg.data}")


def main(args=None):
    rclpy.init(args=args)
    subscriber = Subscriber()
    rclpy.spin(subscriber)
    subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()

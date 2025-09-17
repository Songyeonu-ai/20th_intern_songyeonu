import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import Int32
from std_msgs.msg import Float64


class HelloworldSubscriber(Node):
    def __init__(self):
        super().__init__('helloworld_subscriber')
        self.helloworld_subscriber1 = self.create_subscription(
            String, 
            'topicname', 
            self.subscribe_topic_message,
            10)
        self.helloworld_subscriber2 = self.create_subscription(
            Int32, 
            'topicname_int', 
            self.subscribe_topic_message,
            30)
        self.helloworld_subscriber3 = self.create_subscription(
            Float64, 
            'topicname_float', 
            self.subscribe_topic_message,
            30)

    def subscribe_topic_message(self, msg):
        self.get_logger().info('Received message: {0}'.format(msg.data))



def main(args=None):
    rclpy.init(args=args)
    node = HelloworldSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Keyboard Interrupt (SIGINT)')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
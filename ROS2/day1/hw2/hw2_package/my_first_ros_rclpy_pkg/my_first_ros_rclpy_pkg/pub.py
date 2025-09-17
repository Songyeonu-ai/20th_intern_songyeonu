import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import Int32
from std_msgs.msg import Float64


class HelloworldPublisher(Node):
    def __init__(self):
        super().__init__('helloworld_publisher')
        self.helloworld_publisher1 = self.create_publisher(String, 'topicname', 10)
        self.helloworld_publisher2 = self.create_publisher(Int32, 'topicname_int', 30)
        self.helloworld_publisher3 = self.create_publisher(Float64, 'topicname_float', 30)
        self.timer = self.create_timer(1, self.publish_helloworld_msg)
        self.count=0

    def publish_helloworld_msg(self):
        msg1 = String()
        msg2 = Int32()
        msg3 = Float64()
        msg1.data = 'Hello World: {0}'.format(self.count)
        msg2.data = self.count
        msg3.data = self.count/3
        self.helloworld_publisher1.publish(msg1)
        self.helloworld_publisher2.publish(msg2)
        self.helloworld_publisher3.publish(msg3)
        self.get_logger().info('Published message: {0}'.format(msg1.data))
        self.get_logger().info('Published message: {0}'.format(msg2.data))
        self.get_logger().info('Published message: {0}'.format(msg3.data))
        self.count+=1


def main(args=None):
    rclpy.init(args=args)
    node = HelloworldPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Keyboard Interrupt (SIGINT)')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
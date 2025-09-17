
#include "../include/day4_hw1/subscriber.hpp"

Sub::Sub() : Node("sub")
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    subscriber = this->create_subscription<std_msgs::msg::String>(
        "topicname", 
        qos_profile,
        std::bind(&Sub::topic_callback, this, std::placeholders::_1));
}


void Sub::topic_callback(const std_msgs::msg::String::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg->data.c_str());
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

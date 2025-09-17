#include "../include/my_first_ros_rclcpp_pkg/subscriber.hpp"

Sub::Sub() : Node("sub")
{
    subscriber1 = this ->create_subscription<std_msgs::msg::String>(
        "topicname", 
        10,
        std::bind(&Sub::topic_callback1, this, std::placeholders::_1));
    subscriber2 = this ->create_subscription<std_msgs::msg::Int32>(
        "topicname_int", 
        30,
        std::bind(&Sub::topic_callback2, this, std::placeholders::_1));
    subscriber3 = this ->create_subscription<std_msgs::msg::Float64>(
        "topicname_float", 
        30,
        std::bind(&Sub::topic_callback3, this, std::placeholders::_1));
}

void Sub::topic_callback1(const std_msgs::msg::String::SharedPtr msg1)
{
    RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg1->data.c_str());
}
void Sub::topic_callback2(const std_msgs::msg::Int32::SharedPtr msg2)
{
    RCLCPP_INFO(this->get_logger(), "Received message: '%d'", msg2->data);
}
void Sub::topic_callback3(const std_msgs::msg::Float64::SharedPtr msg3)
{
    RCLCPP_INFO(this->get_logger(), "Received message: '%f'", msg3->data);
}


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
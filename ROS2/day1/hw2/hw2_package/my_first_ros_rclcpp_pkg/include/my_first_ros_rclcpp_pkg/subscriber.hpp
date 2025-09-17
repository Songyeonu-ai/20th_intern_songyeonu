
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"

class Sub : public rclcpp::Node
{
    public:
       Sub();
    private:
       void topic_callback1(const std_msgs::msg::String::SharedPtr msg1);
       void topic_callback2(const std_msgs::msg::Int32::SharedPtr msg2);
       void topic_callback3(const std_msgs::msg::Float64::SharedPtr msg3);
       rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber1;
       rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber2;
       rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber3;
};


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
       void topic_callback(const std_msgs::msg::String::SharedPtr msg);
       rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;

};

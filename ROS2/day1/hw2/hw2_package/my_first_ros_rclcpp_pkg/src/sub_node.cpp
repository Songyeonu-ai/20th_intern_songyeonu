
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
       Sub() : Node("sub")
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

    private:
       void topic_callback1(const std_msgs::msg::String::SharedPtr msg1)
       {
           RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg1->data.c_str());
       }
       rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber1;

       void topic_callback2(const std_msgs::msg::Int32::SharedPtr msg2)
       {
           RCLCPP_INFO(this->get_logger(), "Received message: '%d'", msg2->data);
       }
       rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber2;

       void topic_callback3(const std_msgs::msg::Float64::SharedPtr msg3)
       {
           RCLCPP_INFO(this->get_logger(), "Received message: '%f'", msg3->data);
       }
       rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber3;

};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

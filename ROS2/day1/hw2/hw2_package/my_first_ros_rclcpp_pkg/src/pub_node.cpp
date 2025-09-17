
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals;

class Pub : public rclcpp::Node
{
    public:
       Pub() : Node("pub")
       {
           publisher1 = this->create_publisher<std_msgs::msg::String>("topicname", 10);
           publisher2 = this->create_publisher<std_msgs::msg::Int32>("topicname_int", 30);
           publisher3 = this->create_publisher<std_msgs::msg::Float64>("topicname_float", 30);
           timer = this->create_wall_timer(1s, std::bind(&Pub::timer_callback,this));
       }
       int count=0;

    private:
        rclcpp::TimerBase::SharedPtr timer;
       void timer_callback()
       {
           auto msg1 = std_msgs::msg::String();
           auto msg2 = std_msgs::msg::Int32();
           auto msg3 = std_msgs::msg::Float64();
           msg1.data = "Hello World: " + std::to_string(count++);
           msg2.data = (count);
           msg3.data = (count)/3;
           RCLCPP_INFO(this->get_logger(), "Published message: '%s'", msg1.data.c_str());
           RCLCPP_INFO(this->get_logger(), "Published message: '%d'", msg2.data);
           RCLCPP_INFO(this->get_logger(), "Published message: '%f'", msg3.data);
           publisher1->publish(msg1);
           publisher2->publish(msg2);
           publisher3->publish(msg3);
       }
       rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher1;
       rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher2;
       rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher3;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<Pub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}



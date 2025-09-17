
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"

using namespace std::chrono_literals;


class Pub : public rclcpp::Node
{
    public:
       Pub();
       void draw_square();
       void draw_circle();
       void draw_triang();
       bool end_flag;
       bool command();
       rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
       rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher2;
    private:
       size_t count;
};


// mycpp_publisher_ = this->create_publisher<std_msg::String>("topicname", 10);
// timer_ = this->create_wall_timer(1s, std::bind(&MyCppNode::timer_callback, this));

// private:
//     rclcpp::TimerBase::SharePtr timer_;
//     void timer_callback();
 
//     rclcpp::Publisher<std_msgs::msg::Strimg>::SharePtr mycpp_publisher_;


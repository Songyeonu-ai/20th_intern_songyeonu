
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "sensor_msgs/msg/joy.hpp"


#include <vector>
#include <stdint.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include <custom_interfaces/msg/add_two_ints.hpp>

using namespace std::chrono_literals;

class Sub_and_Pub : public rclcpp::Node
{
    public:
       Sub_and_Pub();

    private:
       void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
       void timer_callback();
       rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subjoy;
       rclcpp::Publisher<custom_interfaces::msg::AddTwoInts>::SharedPtr publisher;
       rclcpp::TimerBase::SharedPtr timer_sub;
       rclcpp::TimerBase::SharedPtr timer_pub;
       int count;
       float velo;
       float rot;
       float max_vel;
       float max_rot;

};


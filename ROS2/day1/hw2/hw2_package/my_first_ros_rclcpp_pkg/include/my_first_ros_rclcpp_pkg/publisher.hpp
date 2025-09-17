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
       Pub();
       int count;

    private:
        rclcpp::TimerBase::SharedPtr timer;
       void timer_callback();
       rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher1;
       rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher2;
       rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher3;
};



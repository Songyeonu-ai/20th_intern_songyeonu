
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

 int timecount=0;

class Sub_and_Pub : public rclcpp::Node
{
    public:
       Sub_and_Pub() : Node("sub")
        {   
            timer_sub = this->create_wall_timer(50ms, std::bind(&Sub_and_Pub::time_count,this)); //500ms마다 초 세기
            auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
            subjoy = this ->create_subscription<sensor_msgs::msg::Joy>(
                "/joy", 
                qos_profile,
                std::bind(&Sub_and_Pub::joy_callback, this, std::placeholders::_1));
            
            publisher = this->create_publisher<custom_interfaces::msg::AddTwoInts>("middle_topic", 10);
            timer_pub = this->create_wall_timer(50ms, std::bind(&Sub_and_Pub::timer_callback,this));


        }
        int count=0;
        int sec = timecount;
        float velo_x = 0;//x-y축(왼쪽 조이스틱)
        float velo_y = 0;
        float rot_x = 0;//오른쪽 조이스틱
        float rot_y = 0;

    private:
       void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
       {
           sec = timecount;
           velo_x = msg->axes[0]; 
           velo_y = msg->axes[1];
           rot_x = msg->axes[3];
           rot_y = msg->axes[4];

           RCLCPP_INFO(this->get_logger(), "Received message: [x_velo:'%f',y_velo:'%f', rot_x:'%f', rot_y:'%f'] ", velo_x, velo_y, rot_x, rot_y);
       }
       rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subjoy;
       rclcpp::Publisher<custom_interfaces::msg::AddTwoInts>::SharedPtr publisher;
       rclcpp::TimerBase::SharedPtr timer_sub;
       rclcpp::TimerBase::SharedPtr timer_pub;

       void time_count(){
            timecount++;
       }

        void timer_callback()
       {
           auto msg = custom_interfaces::msg::AddTwoInts();
           msg.b[0] = velo_x; msg.b[1] = velo_x; msg.b[2] = rot_x; msg.b[3] = rot_y;
           RCLCPP_INFO(this->get_logger(), "Published message: [x_velo:'%f',y_velo:'%f', rot_x:'%f', rot_y:'%f'] ", velo_x, velo_y, rot_x, rot_y);
           publisher->publish(msg);
       }
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub_and_Pub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

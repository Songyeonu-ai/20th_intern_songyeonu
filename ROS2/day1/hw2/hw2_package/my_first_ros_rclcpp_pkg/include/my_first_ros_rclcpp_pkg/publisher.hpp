
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals;


// class Pub : public rclcpp::Node
// {
//     public:
//        Pub() : Node("pub"), count(0)
//        {
//            auto qos_profile = rclcpp::Qos(rclcpp::KeepLast(10));
//            publisher_ = this ->create_pulisher<std_msgs::msg::String>("topic", qos_profile);
//            timer = this->create_wall_timer(
//               500ms, std::bind(&Pub::timer_callback, this));
//        }

//     private:
//        void timer_callback()
//        {
//            auto msg = std_msgs::msg::String();
//            msg.data = "Hello World: " + std::to_string(count++);
//            RCLCPP_INFO(this->get_logger(), "PublishingL '%s'", msg.data.c_str());
//            publisher_->publish(msg);
//        }
//        rclcpp::TimeBase::SharedPtr timer;
//        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
//        size_t count;
// }


// // mycpp_publisher_ = this->create_publisher<std_msg::String>("topicname", 10);
// // timer_ = this->create_wall_timer(1s, std::bind(&MyCppNode::timer_callback, this));

// // private:
// //     rclcpp::TimerBase::SharePtr timer_;
// //     void timer_callback();
 
// //     rclcpp::Publisher<std_msgs::msg::Strimg>::SharePtr mycpp_publisher_;

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv); //ROS 초기화하는 과정...노드의 이름을 갖게 됨
//     auto node = std::make_shared<Pub>();
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }


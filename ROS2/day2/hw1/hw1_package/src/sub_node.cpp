
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <inttypes.h>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include <custom_interfaces/msg/add_two_ints.hpp>

class Sub : public rclcpp::Node
{
    public:
       Sub() : Node("sub")
        {
            subscriber = this ->create_subscription<custom_interfaces::msg::AddTwoInts>(
                "topicname", 
                10,
                std::bind(&Sub::topic_callback, this, std::placeholders::_1));
        }

    private:
       void topic_callback(const custom_interfaces::msg::AddTwoInts & msg)
       {
           RCLCPP_INFO(this->get_logger(),
            "Received message: '[%lld, %lld]'",
            static_cast<long long>(msg.b[0]),
            static_cast<long long>(msg.b[1]));
       }
       rclcpp::Subscription<custom_interfaces::msg::AddTwoInts>::SharedPtr subscriber;

};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

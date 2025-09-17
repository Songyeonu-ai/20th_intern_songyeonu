
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include "../include/day1_hw3/publisher.hpp"


using namespace std::chrono_literals;
using SetPen = turtlesim::srv::SetPen;
using namespace std;

       Pub::Pub() : Node("pub")
       {
           count=0;
           end_flag=false;
           publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 30);
       }

       void Pub::draw_square(){
           auto client = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 255; request->g = 0; request->b = 0;
           request->width = 5;
           request->off = 0;
           auto result = client->async_send_request(request);

           auto msg = geometry_msgs::msg::Twist();
           for(int i=0;i<4;i++){
           msg.linear.x=2.0;
           msg.angular.z=0.0;
           RCLCPP_INFO(this->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           msg.linear.x=0.0;
           msg.angular.z=1.57;
           RCLCPP_INFO(this->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           }

       }
       void Pub::draw_circle(){
        auto client = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 0; request->g = 255; request->b = 0;
           request->width = 10;
           request->off = 0;
           auto result = client->async_send_request(request);
        auto msg = geometry_msgs::msg::Twist();
           for(int i=0;i<4;i++){
           msg.linear.x=2.0;
           msg.angular.z=1.8;
           RCLCPP_INFO(this->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           }

       }
       void Pub::draw_triang(){
        auto client = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 255; request->g = 255; request->b = 255;
           request->width = 15;
           request->off = 0;
           auto result = client->async_send_request(request);
           auto msg = geometry_msgs::msg::Twist();
          for(int i=0;i<3;i++){
           msg.linear.x=2.0;
           msg.angular.z=0.0;
           RCLCPP_INFO(this->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           msg.linear.x=0.0;
           msg.angular.z=2.08;
           RCLCPP_INFO(this->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           }

       }

        bool Pub::command()
       {
           std::string com;
           cout<<"press command key: <W>:circle <A>:square <S>:triangle <D>:exit";
           cin>>com;
           if(com=="W"||com=="w")draw_circle();
           else if(com=="A"||com=="a")draw_square();
           else if(com=="S"||com=="s")draw_triang();
           else if(com=="D"||com=="d")return false;
           else cout<<"Don't press other keys"<<endl;
           return true;
       }


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<Pub>();
    while(1){
        if(!node->command())break;
    }
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}




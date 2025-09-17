/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/hw2/qnode.hpp"
#include <QDebug>


using namespace std::chrono_literals;
using namespace std;

QNode::QNode()
{
  int count=0;
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = std::make_shared<rclcpp::Node>("qnode");
  publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 30);
  // subscriber = node->create_subscription<geometry_msgs::msg::Twist>(
  //               "topicname", 
  //               10,
  //               std::bind(&QNode::topic_callback, this, std::placeholders::_1));
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}

void QNode::draw_square(){
           auto client = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 255; request->g = 0; request->b = 0;
           request->width = 5;
           request->off = 0;
           auto result = client->async_send_request(request);

           auto msg = geometry_msgs::msg::Twist();
           for(int i=0;i<4;i++){
           msg.linear.x=2.0;
           msg.angular.z=0.0;
           RCLCPP_INFO(node->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           emit receivedMessage_1(QString::number(msg.linear.x));
           emit receivedMessage_2(QString::number(msg.angular.z));
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           msg.linear.x=0.0;
           msg.angular.z=1.57;
           RCLCPP_INFO(node->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           emit receivedMessage_1(QString::number(msg.linear.x));
           emit receivedMessage_2(QString::number(msg.angular.z));
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           }

       }
       void QNode::draw_circle(){
        auto client = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 0; request->g = 255; request->b = 0;
           request->width = 10;
           request->off = 0;
           auto result = client->async_send_request(request);
        auto msg = geometry_msgs::msg::Twist();
           for(int i=0;i<4;i++){
           msg.linear.x=2.0;
           msg.angular.z=1.8;
           RCLCPP_INFO(node->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           emit receivedMessage_1(QString::number(msg.linear.x));
           emit receivedMessage_2(QString::number(msg.angular.z));
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           }

       }
       void QNode::draw_triang(){
        auto client = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
           auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
           request->r = 255; request->g = 255; request->b = 255;
           request->width = 15;
           request->off = 0;
           auto result = client->async_send_request(request);
           auto msg = geometry_msgs::msg::Twist();
           for(int i=0;i<3;i++){
           msg.linear.x=2.0;
           msg.angular.z=0.0;
           RCLCPP_INFO(node->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           emit receivedMessage_1(QString::number(msg.linear.x));
           emit receivedMessage_2(QString::number(msg.angular.z));
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           msg.linear.x=0.0;
           msg.angular.z=2.08;
           RCLCPP_INFO(node->get_logger(), "{linear: {x: '%.2f', y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: '%.2f'}}", msg.linear.x, msg.angular.z);
           publisher->publish(msg);
           emit receivedMessage_1(QString::number(msg.linear.x));
           emit receivedMessage_2(QString::number(msg.angular.z));
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           }

       }

// void QNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {
//     qDebug() <<"Received in QNode:" << QString::fromStdString(msg->data);
// }

void QNode::publishing(QString text){
  auto msg = std_msgs::msg::String();
  msg.data = text.toStdString();
  if(msg.data=="W"||msg.data=="w")draw_circle();
           else if(msg.data=="A"||msg.data=="a")draw_square();
           else if(msg.data=="S"||msg.data=="s")draw_triang();
           else if(msg.data=="D"||msg.data=="d")return;
           else cout<<"Don't press other keys"<<endl;
  RCLCPP_INFO(node->get_logger(), "Published message: '%s'", msg.data.c_str());
}


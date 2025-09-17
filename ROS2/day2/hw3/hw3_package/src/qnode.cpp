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

#include "../include/test3/qnode.hpp"
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
  publisher = node->create_publisher<std_msgs::msg::String>("topicname", 10);
  subscriber = node->create_subscription<std_msgs::msg::String>(
                "topicname", 
                10,
                std::bind(&QNode::topic_callback, this, std::placeholders::_1));
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


void QNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {
    qDebug() <<"Received in QNode:" << QString::fromStdString(msg->data);
    emit receivedMessage(QString::fromStdString(msg->data));
}

void QNode::publishing(QString text){
  auto msg = std_msgs::msg::String();
  msg.data = text.toStdString();
  publisher->publish(msg);
  RCLCPP_INFO(node->get_logger(), "Published message: '%s'", msg.data.c_str());
}


/**
 * @file /include/% (package)s/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef hw2_QNODE_HPP_
#define hw2_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  //void topic_callback(const std_msgs::msg::String::SharedPtr msg);
  void publishing(QString text);
  void draw_square();
  void draw_circle();
  void draw_triang();
  //void setMessage(Qstring str);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
  // rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber;

Q_SIGNALS:
  void rosShutDown();
  void receivedMessage_1(QString msg);
  void receivedMessage_2(QString msg);
};

#endif /* % (package)s_QNODE_HPP_ */

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

#ifndef hw4_QNODE_HPP_
#define hw4_QNODE_HPP_

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

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  void topic_callback(const std_msgs::msg::String::SharedPtr msg);
  void publishing(QString text);
  //void setMessage(Qstring str);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;

Q_SIGNALS:
  void rosShutDown();
  void receivedMessage_CW(QString msg);
  void receivedMessage_CCW(QString msg);
};

#endif /* % (package)s_QNODE_HPP_ */

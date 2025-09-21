#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include <custom_interfaces/msg/add_two_ints.hpp>
#include <chrono>
using namespace std::chrono_literals;


class FramePublisher : public rclcpp::Node
{
public:
  FramePublisher();

private:
  rclcpp::Subscription<custom_interfaces::msg::AddTwoInts>::SharedPtr subscription_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::string odom;
  tf2::Quaternion q;
  geometry_msgs::msg::TransformStamped t;
  std::string topic_name;
  std::ostringstream stream;
  rclcpp::TimerBase::SharedPtr timer_pub;
  void timer_count();
  int t_count;
  
};


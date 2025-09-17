// Copyright 2021 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include <custom_interfaces/msg/add_two_ints.hpp>

class FramePublisher : public rclcpp::Node
{
public:
  FramePublisher()
  : Node("hw2_pkg2_node")
  {
    // Declare and acquire `turtlename` parameter
    odom = this->declare_parameter<std::string>("movingframe", "odom");

    // Initialize the transform broadcaster
    tf_broadcaster_ =
      std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    // Subscribe to a turtle{1}{2}/pose topic and call handle_turtle_pose
    // callback function on each message
    std::ostringstream stream;
    stream << "/" << odom.c_str() << "/pose";
    std::string topic_name = stream.str();

    auto handle_odom = [this](const std::shared_ptr<custom_interfaces::msg::AddTwoInts> msg) {
        geometry_msgs::msg::TransformStamped t;

        // Read message content and assign it to
        // corresponding tf variables
        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world";
        t.child_frame_id = odom.c_str();

        // Turtle only exists in 2D, thus we get x and y translation
        // coordinates from the message and set the z coordinate to 0
        t.transform.translation.x = msg->b[0]; //터틀심에서의 x, y값을 받아와 저장...z축은 없음.
        t.transform.translation.y = msg->b[1];
        t.transform.translation.z = 0.0;

        // For the same reason, turtle can only rotate around one axis
        // and this why we set rotation in x and y to 0 and obtain
        // rotation in z axis from the message
        tf2::Quaternion q;
        q.setRPY(0, 0, msg->b[2]+msg->b[3]); //여기서 b의 [2]에는 theta가 있어야 함
        t.transform.rotation.x = q.x(); //이동?
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z(); 
        t.transform.rotation.w = q.w();

        // Send the transformation
        tf_broadcaster_->sendTransform(t);
      };
    subscription_ = this->create_subscription<custom_interfaces::msg::AddTwoInts>( //여기서 터틀심 받아오기...나는 다른거 받아와야함
      "middle_topic", 10,
      handle_odom);
  }

private:
  rclcpp::Subscription<custom_interfaces::msg::AddTwoInts>::SharedPtr subscription_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::string odom;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FramePublisher>());
  rclcpp::shutdown();
  return 0;
}

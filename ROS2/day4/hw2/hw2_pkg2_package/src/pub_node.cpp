#include "../include/hw2_pkg2/publisher.hpp"

  FramePublisher::FramePublisher(): Node("hw2_pkg2_node")
  {
    t_count=0;
    odom = this->declare_parameter<std::string>("movingframe", "odom");

    tf_broadcaster_ =
      std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    stream << "/" << odom.c_str() << "/pose";
    topic_name = stream.str();
    timer_pub = this->create_wall_timer(100ms, std::bind(&FramePublisher::timer_count,this));

    auto handle_odom = [this](const std::shared_ptr<custom_interfaces::msg::AddTwoInts> msg) {
        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world";
        t.child_frame_id = odom.c_str();

        t.transform.translation.x = 0.0;
        t.transform.translation.y = msg->b[0]*t_count;
        t.transform.translation.z = 0.0;

        q.setRPY(0, 0, msg->b[1]*t_count);
        t.transform.rotation.x = q.x(); 
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z(); 
        t.transform.rotation.w = q.w();

        // Send the transformation
        tf_broadcaster_->sendTransform(t);
      };
      subscription_ = this->create_subscription<custom_interfaces::msg::AddTwoInts>( //여기서 각속/선속 받아오기
      "middle_topic", 10,
      handle_odom);
  }
  void FramePublisher::timer_count(){
     t_count++;
  }

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FramePublisher>());
  rclcpp::shutdown();
  return 0;
}

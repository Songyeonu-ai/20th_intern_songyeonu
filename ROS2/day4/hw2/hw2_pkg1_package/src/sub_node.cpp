#include "../include/hw2_pkg1/subscriber.hpp" 


Sub_and_Pub::Sub_and_Pub() : Node("sub")
{   
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    subjoy = this ->create_subscription<sensor_msgs::msg::Joy>(
    "/joy", 
    qos_profile,
    std::bind(&Sub_and_Pub::joy_callback, this, std::placeholders::_1));
            
    publisher = this->create_publisher<custom_interfaces::msg::AddTwoInts>("middle_topic", 10);
    timer_pub = this->create_wall_timer(50ms, std::bind(&Sub_and_Pub::timer_callback,this));
    
    count=0;
    velo= 0;
    rot = 0;
    max_vel = 0.5;
    max_rot = 0.5;
}


void Sub_and_Pub::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    velo = msg->axes[1]; 
    rot = msg->axes[0];

    RCLCPP_INFO(this->get_logger(), "Received message: [x_velo:'%f', rot:'%f'] ", velo, rot);
}


void Sub_and_Pub::timer_callback()
{
    auto msg = custom_interfaces::msg::AddTwoInts();
    msg.b[0] = velo*max_vel; msg.b[1] = rot*max_rot;
    RCLCPP_INFO(this->get_logger(), "Published message: [velo:'%f', rot:'%f'] ", velo, rot);
    publisher->publish(msg);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub_and_Pub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

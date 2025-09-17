
#include "../include/day4_hw1/publisher.hpp"

using namespace std::chrono_literals;

Pub::Pub()
    : rclcpp_lifecycle::LifecycleNode("pub"), count(0){}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_configure(const rclcpp_lifecycle::State &state)
{//configuaring 상태에 있음
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
    qos_profile.durability(RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL);
    publisher = this->create_publisher<std_msgs::msg::String>("topicname", qos_profile);
    timer = this->create_wall_timer(1s, std::bind(&Pub::timer_callback, this));

    RCUTILS_LOG_INFO_NAMED(get_name(), "Configuring from state %s.", state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_activate(const rclcpp_lifecycle::State &state)
{
    publisher->on_activate();
    RCUTILS_LOG_INFO_NAMED(get_name(), "Activating from state %s.", state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_deactivate(const rclcpp_lifecycle::State &state)
{
    publisher->on_deactivate();
    RCUTILS_LOG_INFO_NAMED(get_name(), "Deactivating from state %s.", state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_cleanup(const rclcpp_lifecycle::State &state)
{

    timer.reset();
    publisher.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "CleaningUp from state %s.", state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_shutdown(const rclcpp_lifecycle::State &state)
{
    timer.reset();
    publisher.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "ShuttingDown from state %s.", state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}
rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn Pub::on_error(const rclcpp_lifecycle::State &state)
  {
 
    RCUTILS_LOG_INFO_NAMED(get_name(), "something went wrong!");
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::FAILURE;
  }

void Pub::timer_callback()
{
    auto message = std_msgs::msg::String();
    message.data = "Say Hello #" + std::to_string(count++);
    if (!publisher->is_activated())
    {
        RCLCPP_INFO(
            get_logger(), "Lifecycle publisher is currently inactive. Messages are not published.");
    }
    else
    {
        RCLCPP_INFO(get_logger(), "Lifecycle publisher is active. Publishing: [%s]", message.data.c_str());
    }
    publisher->publish(message);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<Pub> pub = std::make_shared<Pub>();
    rclcpp::spin(pub->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}

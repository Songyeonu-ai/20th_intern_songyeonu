
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include <custom_interfaces/msg/add_two_ints.hpp>

using namespace std::chrono_literals;
using namespace std;

class Pub : public rclcpp::Node
{
    public:
       bool input_flag=false;
       char input[100]={0};
       long inp=0;
       Pub() : Node("pub")
       {
           publisher = this->create_publisher<custom_interfaces::msg::AddTwoInts>("topicname", 10);
           timer = this->create_wall_timer(1s, std::bind(&Pub::timer_callback,this));
       }
    //    void user_inp(){
    //         cout<<"정수를 1개 입력하세요: ";
    //         cin>>inp;
    //         // for(int i=0;i<strlenn(input);i++){
    //         //     if(input[i]==' ')continue;
    //         //     inp[i]=long(input[i]);
    //         // }
    //    }
       
       int strlenn(const char *str){
        int len=0;
        while(*str){
            len++;
            str++;
        }
        return len;
       }

    private:
        rclcpp::TimerBase::SharedPtr timer;
       int count=0;
       void timer_callback()
       {
           auto msg = custom_interfaces::msg::AddTwoInts();
           //user_inp();
        //    for(int i=0;i<2;i++){
        //        msg.b[i]=inp[i];
        //    }
           msg.b[0]=0;
           msg.b[1]=1;
           RCLCPP_INFO(this->get_logger(), "Published message: '[%ld, %ld]'", msg.b[0], msg.b[1]);
           publisher->publish(msg);
       }
       rclcpp::Publisher<custom_interfaces::msg::AddTwoInts>::SharedPtr publisher;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<Pub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}



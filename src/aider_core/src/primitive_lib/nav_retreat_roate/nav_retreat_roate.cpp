#include "aider_core/primitive_lib/nav_retreat_roate/nav_retreat_roate.hpp"

using nav_interfaces::srv::NavCarryBoxRetreaatAndRoate;
using namespace std::chrono_literals;
//用到参数
//无
NavCarryBoxRetreaatAndRoatePrimitive::NavCarryBoxRetreaatAndRoatePrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：搬箱子后退旋转动作已激活！");//在NavCarryBoxRetreaatAndRoatePrimitive动作基元库中传递大脑节点
    //在NavCarryBoxRetreaatAndRoatePrimitive动作基元库解析函数中实例化需要用到的服务通信
    nav_retreat_roate_client_ = std::make_shared<TemplateClientService<NavCarryBoxRetreaatAndRoate>>();
    nav_retreat_roate_client_->Create("nav_carry_box_retreat_roate");//创立服务通讯客户端
}

bool NavCarryBoxRetreaatAndRoatePrimitive::Excute() {
    //检测服务端有无连接
    if(nav_retreat_roate_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    RCLCPP_INFO(aider_node->get_logger(),"后退旋转开始执行！");
    //设置服务通讯请求与应答应变量
    nav_interfaces::srv::NavCarryBoxRetreaatAndRoate::Request nav_retreat_roate_request;
    nav_interfaces::srv::NavCarryBoxRetreaatAndRoate::Response nav_retreat_roate_response;
    //向服务端发送请求并获取服务端返回数据
    nav_retreat_roate_request.start_flag = true;
    if(nav_retreat_roate_client_->SendRequest(&nav_retreat_roate_request,&nav_retreat_roate_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至导航服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(nav_retreat_roate_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"后退旋转失败！");
        return 0;
    }   
    RCLCPP_INFO(aider_node->get_logger(),"后退旋转成功！");
    return 1;

}

void NavCarryBoxRetreaatAndRoatePrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("NavCarryBoxRetreaatAndRoatePrimitive"), "Stop function called.");
}


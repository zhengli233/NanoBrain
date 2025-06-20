#include "aider_core/primitive_lib/crouch/crouch.hpp"

using lowerbody_interfaces::srv::Crouch;
using namespace std::chrono_literals;
//用到参数
//输入：crouch_height

CrouchPrimitive::CrouchPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "crouch_height");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：下蹲已激活！");//在CrouchPrimitive动作基元库中传递大脑节点
    //在CrouchPrimitive动作基元库解析函数中实例化需要用到的服务通信
    crouch_to_client_ = std::make_shared<TemplateClientService<Crouch>>();
    crouch_to_client_->Create("crouch_to");//创立服务通讯客户端
}

bool CrouchPrimitive::Excute() {
    //检测服务端有无连接
    if(crouch_to_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    lowerbody_interfaces::srv::Crouch::Request crouch_request;
    lowerbody_interfaces::srv::Crouch::Response crouch_response;
    //向服务端发送请求并获取服务端返回数据
    crouch_request.crouch_height = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"crouch_height").value());
    if(crouch_to_client_->SendRequest(&crouch_request,&crouch_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至下肢服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(crouch_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"下蹲失败！");
        return 0;
    }
    RCLCPP_INFO(aider_node->get_logger(), "下蹲成功！");
    return 1;

}

void CrouchPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("CrouchPrimitive"), "Stop function called.");
}


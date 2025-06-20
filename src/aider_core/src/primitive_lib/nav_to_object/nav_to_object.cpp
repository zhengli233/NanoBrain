#include "aider_core/primitive_lib/nav_to_object/nav_to_object.hpp"

using nav_interfaces::srv::NavToObject;
using namespace std::chrono_literals;
//用到参数
//输入：object_name
NavToObjectPrimitive::NavToObjectPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "object_name");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：导航到指定物品已激活！");//在NavToObjectPrimitive动作基元库中传递大脑节点
    //在NavToObjectPrimitive动作基元库解析函数中实例化需要用到的服务通信
    nav_to_object_client_ = std::make_shared<TemplateClientService<NavToObject>>();
    nav_to_object_client_->Create("nav_to_object");//创立服务通讯客户端
}

bool NavToObjectPrimitive::Excute() {
    //检测服务端有无连接
    if(nav_to_object_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    nav_interfaces::srv::NavToObject::Request nav_to_object_request;
    nav_interfaces::srv::NavToObject::Response nav_to_object_response;
    //向服务端发送请求并获取服务端返回数据
    nav_to_object_request.object_label = std::any_cast<std::string>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"object_name").value());
    if(nav_to_object_client_->SendRequest(&nav_to_object_request,&nav_to_object_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至导航服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(nav_to_object_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"导航到物体失败！");
        return 0;
    }   
    RCLCPP_INFO(aider_node->get_logger(),"导航成功！");
    return 1;

}

void NavToObjectPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("NavToObjectPrimitive"), "Stop function called.");
}


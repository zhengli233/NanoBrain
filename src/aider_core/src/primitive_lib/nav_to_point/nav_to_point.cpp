#include "aider_core/primitive_lib/nav_to_point/nav_to_point.hpp"

using nav_interfaces::srv::NavToPoint;
using namespace std::chrono_literals;
//用到参数
//输入：nav_to_target_x
//输入：nav_to_target_y
//输入：nav_to_target_oriention_x
//输入：nav_to_target_oriention_y
//输入：nav_to_target_oriention_z
//输入：nav_to_target_oriention_w
NavToPointPrimitive::NavToPointPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_oriention_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_oriention_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_oriention_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "nav_to_target_oriention_w");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：导航到指定坐标点已激活！");//在NavToPointPrimitive动作基元库中传递大脑节点
    //在NavToPointPrimitive动作基元库解析函数中实例化需要用到的服务通信
    nav_to_point_client_ = std::make_shared<TemplateClientService<NavToPoint>>();
    nav_to_point_client_->Create("nav_to_point");//创立服务通讯客户端
}

bool NavToPointPrimitive::Excute() {
    //检测服务端有无连接
    if(nav_to_point_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    nav_interfaces::srv::NavToPoint::Request nav_to_point_request;
    nav_interfaces::srv::NavToPoint::Response nav_to_point_response;
    //向服务端发送请求并获取服务端返回数据
    nav_to_point_request.target_point.pose.position.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_x").value());
    nav_to_point_request.target_point.pose.position.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_y").value());
    nav_to_point_request.target_point.pose.orientation.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_oriention_x").value());
    nav_to_point_request.target_point.pose.orientation.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_oriention_y").value());
    nav_to_point_request.target_point.pose.orientation.z = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_oriention_z").value());
    nav_to_point_request.target_point.pose.orientation.w = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"nav_to_target_oriention_w").value());
    if(nav_to_point_client_->SendRequest(&nav_to_point_request,&nav_to_point_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至导航服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(nav_to_point_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"导航到目标点失败！");
        return 0;
    }   
    RCLCPP_INFO(aider_node->get_logger(),"导航成功！");
    return 1;

}

void NavToPointPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("NavToPointPrimitive"), "Stop function called.");
}


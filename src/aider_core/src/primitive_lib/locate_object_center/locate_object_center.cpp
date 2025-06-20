#include "aider_core/primitive_lib/locate_object_center/locate_object_center.hpp"

using vision_interfaces::srv::LocateObjectCenter;
using namespace std::chrono_literals;
//用到参数
//输入：object_name
//输出：left_target_orientation_x
//输出：left_target_orientation_y
//输出：left_target_orientation_z
//输出：left_target_orientation_w
//输出：left_target_position_x
//输出：left_target_position_y
//输出：left_target_position_z
LocateCenterPrimitive::LocateCenterPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "object_name");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_w");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_z");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：定位物体坐标点已激活！");//在LocateCenterPrimitive动作基元库中传递大脑节点
    //在LocateCenterPrimitive动作基元库解析函数中实例化需要用到的服务通信
    center_ask_client_ = std::make_shared<TemplateClientService<LocateObjectCenter>>();
    center_ask_client_->Create("locate_center");//创立服务通讯客户端
}

bool LocateCenterPrimitive::Excute() {
    //检测服务端有无连接
    if(center_ask_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    vision_interfaces::srv::LocateObjectCenter::Request center_request;
    vision_interfaces::srv::LocateObjectCenter::Response center_response;
    //向服务端发送请求并获取服务端返回数据
    center_request.object_label = std::any_cast<std::string>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"object_name").value());
    if(center_ask_client_->SendRequest(&center_request,&center_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至视觉服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(center_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"视觉识别失败！");
        return 0;
    }
    //对目标位姿进行赋值
    this->target_orientation_x = center_response.orientation.x;
    this->target_orientation_y = center_response.orientation.y;
    this->target_orientation_z = center_response.orientation.z;
    this->target_orientation_w = center_response.orientation.w;
    this->target_position_x = center_response.position.x;
    this->target_position_y = center_response.position.y;
    this->target_position_z = center_response.position.z;
    this->param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_x", target_orientation_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_y", target_orientation_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_z", target_orientation_z);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_w", target_orientation_w);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_x", target_position_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_y", target_position_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_z", target_position_z);
    //打印出目标中心点坐标
    RCLCPP_INFO(aider_node->get_logger(),"物品%s中心坐标: x:%f,y:%f,z:%f",
                                    center_request.object_label.c_str(),
                                    center_response.position.x,
                                    center_response.position.y,
                                    center_response.position.z);
    
    return 1;

}

void LocateCenterPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("LocateCenterPrimitive"), "Stop function called.");
}


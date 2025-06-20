#include "aider_core/primitive_lib/single_arm_move_to/single_arm_move_to.hpp"

using arm_interfaces::srv::SingleArmMove;
using namespace std::chrono_literals;
//用到参数
//输入：which_arm
//
//输入：left_target_orientation_x
//输入：left_target_orientation_y
//输入：left_target_orientation_z
//输入：left_target_orientation_w
//输入：left_target_position_x
//输入：left_target_position_y
//输入：left_target_position_z
//或者
//输入：right_target_orientation_x
//输入：right_target_orientation_y
//输入：right_target_orientation_z
//输入：right_target_orientation_w
//输入：right_target_position_x
//输入：right_target_position_y
//输入：right_target_position_z
//

SingleArmMoveToPrimitive::SingleArmMoveToPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "which_arm");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_w");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_w");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_z");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：单臂运动指定坐标点已激活！");//在SingleArmMoveToPrimitive动作基元库中传递大脑节点
    //在SingleArmMoveToPrimitive动作基元库解析函数中实例化需要用到的服务通信
    single_arm_move_to_client_ = std::make_shared<TemplateClientService<SingleArmMove>>();
    //创立手臂通讯服务端
    single_arm_move_to_client_->Create("single_arm_move_to");//创立服务通讯客户端
}

bool SingleArmMoveToPrimitive::Excute() {
    //检测服务端有无连接
    if(single_arm_move_to_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至手臂服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    arm_interfaces::srv::SingleArmMove::Request single_arm_move_request;
    arm_interfaces::srv::SingleArmMove::Response arm_move_response;
    //向服务端发送请求并获取服务端返回数据
    single_arm_move_request.which_arm=this->which_arm;
    single_arm_move_request.which_arm = std::any_cast<std::string>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"which_arm").value());
    if (single_arm_move_request.which_arm == "left_arm") {
        single_arm_move_request.orientation.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_orientation_x").value());
        single_arm_move_request.orientation.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_orientation_y").value());
        single_arm_move_request.orientation.z = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_orientation_z").value());
        single_arm_move_request.orientation.w = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_orientation_w").value());
        single_arm_move_request.position.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_position_x").value());
        single_arm_move_request.position.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_position_y").value());
        single_arm_move_request.position.z = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"left_target_position_z").value());
    }
    else {
        single_arm_move_request.orientation.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_orientation_x").value());
        single_arm_move_request.orientation.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_orientation_y").value());
        single_arm_move_request.orientation.z = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_orientation_z").value());
        single_arm_move_request.orientation.w = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_orientation_w").value());
        single_arm_move_request.position.x = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_position_x").value());
        single_arm_move_request.position.y = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_position_y").value());
        single_arm_move_request.position.z = std::any_cast<double>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"right_target_position_z").value());
    }
    
    if(single_arm_move_to_client_->SendRequest(&single_arm_move_request,&arm_move_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至手臂服务器，连接失败，程序退出！");
        return 0;
    }
    //判断点位是否到达成功
    if(arm_move_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"移动失败！");
        return 0;
    }

    RCLCPP_INFO(aider_node->get_logger(),"抓取成功！");
    return 1;

}

void SingleArmMoveToPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("SingleArmMoveToPrimitive"), "Stop function called.");
}


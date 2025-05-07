#include "aider_core/primitive_lib/single_arm_move_to/single_arm_move_to.hpp"

using arm_interfaces::srv::SingleArmMove;
using namespace std::chrono_literals;


SingleArmMoveToPrimitive::SingleArmMoveToPrimitive() {
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：单臂运动指定坐标点已激活！");//在SingleArmMoveToPrimitive动作基元库中传递大脑节点
    //初始化参数列表
    REGISTER_PARAM("which_arm", std::string, which_arm);
    REGISTER_PARAM("target_orientation_x", double, target_orientation_x);
    REGISTER_PARAM("target_orientation_y", double, target_orientation_y);
    REGISTER_PARAM("target_orientation_z", double, target_orientation_z);
    REGISTER_PARAM("target_orientation_w", double,target_orientation_w);
    REGISTER_PARAM("target_position_x", double, target_position_x);
    REGISTER_PARAM("target_position_y", double, target_position_y);
    REGISTER_PARAM("target_position_z", double, target_position_z);
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
    single_arm_move_request.orientation.x=this->target_orientation_x;
    single_arm_move_request.orientation.y=this->target_orientation_y;
    single_arm_move_request.orientation.z=this->target_orientation_z;
    single_arm_move_request.orientation.w=this->target_orientation_w;
    single_arm_move_request.position.x=this->target_position_x;
    single_arm_move_request.position.y=this->target_position_y;
    single_arm_move_request.position.z=this->target_position_z;
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


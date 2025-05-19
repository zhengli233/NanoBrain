#include "aider_core/primitive_lib/double_arm_move_to/double_arm_move_to.hpp"

using arm_interfaces::srv::DoubleArmMove;
using namespace std::chrono_literals;


DoubleArmMovePrimitive::DoubleArmMovePrimitive() {
    aider_node = AiderNode::get_instance();
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：双臂臂运动指定坐标点已激活！");//在DoubleArmMovePrimitive动作基元库中传递大脑节点
    //初始化参数列表
    REGISTER_PARAM("target_left_orientation_x", double, left_target_orientation_x);
    REGISTER_PARAM("target_left_orientation_y", double, left_target_orientation_y);
    REGISTER_PARAM("target_left_orientation_z", double, left_target_orientation_z);
    REGISTER_PARAM("target_left_orientation_w", double,left_target_orientation_w);
    REGISTER_PARAM("target_left_position_x", double, left_target_position_x);
    REGISTER_PARAM("target_left_position_y", double, left_target_position_y);
    REGISTER_PARAM("target_left_position_z", double, left_target_position_z);
    REGISTER_PARAM("target_right_orientation_x", double, right_target_orientation_x);
    REGISTER_PARAM("target_right_orientation_y", double, right_target_orientation_y);
    REGISTER_PARAM("target_right_orientation_z", double, right_target_orientation_z);
    REGISTER_PARAM("target_right_orientation_w", double,right_target_orientation_w);
    REGISTER_PARAM("target_right_position_x", double, right_target_position_x);
    REGISTER_PARAM("target_right_position_y", double, right_target_position_y);
    REGISTER_PARAM("target_right_position_z", double, right_target_position_z);
    //在DoubleArmMovePrimitivePrimitive动作基元库解析函数中实例化需要用到的服务通信
    double_arm_move_to_client_ = std::make_shared<TemplateClientService<DoubleArmMove>>();
    //创立手臂通讯服务端
    double_arm_move_to_client_->Create("double_arm_move_to");//创立服务通讯客户端
}

bool DoubleArmMovePrimitive::Excute() {
    //检测服务端有无连接
    if(double_arm_move_to_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至手臂服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    arm_interfaces::srv::DoubleArmMove::Request double_arm_move_request;
    arm_interfaces::srv::DoubleArmMove::Response arm_move_response;
    //向服务端发送请求并获取服务端返回数据
    double_arm_move_request.left_orientation.x=this->left_target_orientation_x;
    double_arm_move_request.left_orientation.y=this->left_target_orientation_y;
    double_arm_move_request.left_orientation.z=this->left_target_orientation_z;
    double_arm_move_request.left_orientation.w=this->left_target_orientation_w;
    double_arm_move_request.left_position.x=this->left_target_position_x;
    double_arm_move_request.left_position.y=this->left_target_position_y;
    double_arm_move_request.left_position.z=this->left_target_position_z;

    double_arm_move_request.right_orientation.x=this->right_target_orientation_x;
    double_arm_move_request.right_orientation.y=this->right_target_orientation_y;
    double_arm_move_request.right_orientation.z=this->right_target_orientation_z;
    double_arm_move_request.right_orientation.w=this->right_target_orientation_w;
    double_arm_move_request.right_position.x=this->right_target_position_x;
    double_arm_move_request.right_position.y=this->right_target_position_y;
    double_arm_move_request.right_position.z=this->right_target_position_z;

    if(double_arm_move_to_client_->SendRequest(&double_arm_move_request,&arm_move_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至手臂服务器，连接失败，程序退出！");
        return 0;
    }
    //判断点位是否到达成功
    if(arm_move_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"移动失败！");
        return 0;
    }

    RCLCPP_INFO(aider_node->get_logger(),"成功！");
    return 1;

}

void DoubleArmMovePrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("DoubleArmMovePrimitive"), "Stop function called.");
}


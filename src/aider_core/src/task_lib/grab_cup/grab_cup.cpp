#include "aider_core/task_lib/grab_cup/grab_cup.hpp"



GrapCupTask::GrapCupTask(std::shared_ptr<rclcpp::Node> node)
    :node_(node){
    RCLCPP_INFO(node_->get_logger(), "主节点已共享！");//在grapcup动作库中传递大脑节点
    locate_object_center_ = std::make_shared<LocateCenterPrimitive>(node_);//创建定位物体中心点动作基元
    single_arm_move_to_ = std::make_shared<SingleArmMoveToPrimitive>(node_);//创建单手臂运动动作基元
}

void GrapCupTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "杯子抓取任务已开启！");
    //对获取物品中心坐标点动作基元传递参数
    locate_object_center_->write_param("object_label",std::string("cup"));
    //执行对应动作基元
    if(locate_object_center_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"获取物品中心坐标点失败！");
        return;
    }
    //对目标位姿进行赋值
    double target_orientation_x = locate_object_center_->result<double>("target_orientation_x");
    double target_orientation_y = locate_object_center_->result<double>("target_orientation_y");
    double target_orientation_z = locate_object_center_->result<double>("target_orientation_z");
    double target_orientation_w = locate_object_center_->result<double>("target_orientation_w");
    double target_position_x = locate_object_center_->result<double>("target_position_x");
    double target_position_y = locate_object_center_->result<double>("target_position_y");
    double target_position_z = locate_object_center_->result<double>("target_position_z");

    //对单臂运动动作基元传递参数
    single_arm_move_to_->write_param("which_arm",std::string("left_arm"));
    single_arm_move_to_->write_param("target_orientation_x",target_orientation_x);
    single_arm_move_to_->write_param("target_orientation_y",target_orientation_y);
    single_arm_move_to_->write_param("target_orientation_z",target_orientation_z);
    single_arm_move_to_->write_param("target_orientation_w",target_orientation_w);
    single_arm_move_to_->write_param("target_position_x",target_position_x);
    single_arm_move_to_->write_param("target_position_y",target_position_y);
    single_arm_move_to_->write_param("target_position_z",target_position_z);
    //执行对应动作基元
    if(single_arm_move_to_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"单臂运动至目标点失败！");
        return;
    }
}

void GrapCupTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "Stop function called.");
}






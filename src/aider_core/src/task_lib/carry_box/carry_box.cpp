#include "aider_core/task_lib/carry_box/carry_box.hpp"



CarryBoxTask::CarryBoxTask() {
    aider_node = AiderNode::get_instance();
    RCLCPP_INFO(aider_node->get_logger(), "主节点已共享！");//在carrybox动作库中传递大脑节点
    crouch_ = std::make_shared<CrouchPrimitive>();//创建下蹲动作基元
    double_arm_move_to_ = std::make_shared<DoubleArmMovePrimitive>();//创建双臂操作动作基元
}

void CarryBoxTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "箱子搬运抓取任务已开启！");
    //下蹲动作基元传递参数
    crouch_->write_param("crouch_height",100.0);
    //执行对应下蹲动作基元
    if(crouch_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"下蹲失败！");
        return;
    }

    //对双臂操作动作基元传递参数  //张开
    double_arm_move_to_->write_param("target_left_orientation_x",0.757);
    double_arm_move_to_->write_param("target_left_orientation_y",-0.612);
    double_arm_move_to_->write_param("target_left_orientation_z",0.22);
    double_arm_move_to_->write_param("target_left_orientation_w",-0.067);
    double_arm_move_to_->write_param("target_left_position_x",0.416);
    double_arm_move_to_->write_param("target_left_position_y",0.4);
    double_arm_move_to_->write_param("target_left_position_z",0.648);
    double_arm_move_to_->write_param("target_right_orientation_x",0.946);
    double_arm_move_to_->write_param("target_right_orientation_y",-0.227);
    double_arm_move_to_->write_param("target_right_orientation_z",0.187);
    double_arm_move_to_->write_param("target_right_orientation_w",-0.134);
    double_arm_move_to_->write_param("target_right_position_x",0.416);
    double_arm_move_to_->write_param("target_right_position_y",-0.4);
    double_arm_move_to_->write_param("target_right_position_z",0.648);
    //执行对应双臂动作基元
    if(double_arm_move_to_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }
    //抓取姿态
    double_arm_move_to_->write_param("target_left_orientation_x",0.757);
    double_arm_move_to_->write_param("target_left_orientation_y",-0.612);
    double_arm_move_to_->write_param("target_left_orientation_z",0.22);
    double_arm_move_to_->write_param("target_left_orientation_w",-0.067);
    double_arm_move_to_->write_param("target_left_position_x",0.416);
    double_arm_move_to_->write_param("target_left_position_y",0.19);
    double_arm_move_to_->write_param("target_left_position_z",0.648);
    double_arm_move_to_->write_param("target_right_orientation_x",0.946);
    double_arm_move_to_->write_param("target_right_orientation_y",-0.227);
    double_arm_move_to_->write_param("target_right_orientation_z",0.187);
    double_arm_move_to_->write_param("target_right_orientation_w",-0.134);
    double_arm_move_to_->write_param("target_right_position_x",0.416);
    double_arm_move_to_->write_param("target_right_position_y",-0.19);
    double_arm_move_to_->write_param("target_right_position_z",0.648);
    //执行对应双臂动作基元
    if(double_arm_move_to_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }
    //下蹲动作基元传递参数
    crouch_->write_param("crouch_height",0.0);
    //执行对应下蹲动作基元
    if(crouch_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"下蹲失败！");
        return;
    }


}

void CarryBoxTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "Stop function called.");
}






#include "aider_core/task_lib/carry_box/carry_box.hpp"
int CarryBoxTask::carrybox_instance_counter_ = 0;


CarryBoxTask::CarryBoxTask() {
    carrybox_instance_counter_++;
    now_carrybox_instance_counter_ = carrybox_instance_counter_; 
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    RCLCPP_INFO(aider_node->get_logger(), "主节点已共享！");//在carrybox动作库中传递大脑节点
    nav_to_object_ = std::make_shared<NavToObjectPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建导航寻物动作基元
    nav_retreat_roate_ = std::make_shared<NavCarryBoxRetreaatAndRoatePrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建导航后退旋转动作基元
    nav_to_point_ = std::make_shared<NavToPointPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建导航到目标点基元
    crouch_ = std::make_shared<CrouchPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建下蹲动作基元
    double_arm_move_to_cartesian_ = std::make_shared<DoubleArmMoveCartesianPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建双臂操作动作基元
    double_arm_move_to_cartesian_1_ = std::make_shared<DoubleArmMoveCartesianPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建双臂操作动作基元
    double_arm_move_to_cartesian_2_ = std::make_shared<DoubleArmMoveCartesianPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建双臂操作动作基元
    double_arm_move_to_cartesian_3_ = std::make_shared<DoubleArmMoveCartesianPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建双臂操作动作基元
    double_arm_move_to_cartesian_4_ = std::make_shared<DoubleArmMoveCartesianPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建双臂操作动作基元
    crouch_1_ = std::make_shared<CrouchPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建下蹲动作基元
}

void CarryBoxTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "箱子搬运抓取任务已开启！");
    //导航到指定目标点基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_x", -3.499);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_y", -0.662);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_oriention_x", 0.0);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_oriention_y", 0.0);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_oriention_z", 1.0);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "nav_to_target_oriention_w", 0.0);
    if(nav_to_point_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"导航到指定目标点失败！");
        return;
    }
    //导航后退旋转基元传递参数
    if(nav_retreat_roate_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"导航后退旋转失败！");
        return;
    }
    //导航寻物基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "object_name", std::string("box"));
    if(nav_to_object_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"导航失败！");
        return;
    }
    //下蹲动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "crouch_height", 50.0);
    //执行对应下蹲动作基元
    if(crouch_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"下蹲失败！");
        return;
    }
    rclcpp::sleep_for(5s);
    //抓取姿态
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_x",0.757);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_y",-0.612);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_z", 0.22);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_w", -0.067);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_y", 0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_z", 0.63);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_x", 0.946);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_y", -0.227);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_z", 0.187);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_w", -0.134);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_y", -0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_z", 0.63);
    //执行对应双臂动作基元
    if(double_arm_move_to_cartesian_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }

    //抬升姿态
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_x",0.757);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_y",-0.612);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_z", 0.22);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_w", -0.067);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_x", 0.416);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_y", 0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_z", 0.71);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_x", 0.946);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_y", -0.227);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_z", 0.187);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_w", -0.134);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_x", 0.416);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_y", -0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_z", 0.71);
    //执行对应双臂动作基元
    if(double_arm_move_to_cartesian_1_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }
    //等待用户终端输入指令触发放箱子
    std::string input;
    std::cout << "请输入字母 'y' 以继续执行任务: ";
    std::cin >> input;
    while (input != "y" && input != "Y") {
        std::cout << "输入无效，请重新输入 'y': ";
        std::cin >> input;
    }

    //放下箱子姿态
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_x",0.757);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_y",-0.612);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_z", 0.22);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_w", -0.067);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_y", 0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_z", 0.68);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_x", 0.946);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_y", -0.227);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_z", 0.187);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_w", -0.134);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_y", -0.19);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_z", 0.68);
    //执行对应双臂动作基元
    if(double_arm_move_to_cartesian_2_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }

    //松开箱子
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_x",0.757);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_y",-0.612);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_z", 0.22);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_w", -0.067);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_y", 0.28);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_z", 0.68);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_x", 0.946);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_y", -0.227);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_z", 0.187);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_w", -0.134);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_x", 0.45);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_y", -0.28);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_z", 0.68);
    //执行对应双臂动作基元
    if(double_arm_move_to_cartesian_3_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }

    //回到初始姿态
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_x",0.757);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_y",-0.612);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_z", 0.22);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_orientation_w", -0.067);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_x", 0.416);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_y", 0.40);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "left_target_position_z", 0.648);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_x", 0.946);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_y", -0.227);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_z", 0.187);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_orientation_w", -0.134);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_x", 0.416);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_y", -0.40);
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "right_target_position_z", 0.648);
    //执行对应双臂动作基元
    if(double_arm_move_to_cartesian_4_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"双臂规划运动失败！");
        return;
    }

    //下蹲动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "crouch_height", 0.0);
    //执行对应下蹲动作基元
    if(crouch_1_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"下蹲失败！");
        return;
    }
    rclcpp::sleep_for(5s);

}

void CarryBoxTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "Stop function called.");
}

bool CarryBoxTask::SetParams(std::vector<std::string> params) {
    (void)params;
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "搬箱子任务无参数输入");
    return true;
}

std::string CarryBoxTask::GetTaskName() {
    return "CarryBox";
}

int CarryBoxTask::GetTaskCounter() {
    return now_carrybox_instance_counter_;
}




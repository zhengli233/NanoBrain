#include "aider_core/task_lib/grab_cup/grab_cup.hpp"
int GrapCupTask::grabcup_instance_counter_ = 0;


GrapCupTask::GrapCupTask() {
    grabcup_instance_counter_++;
    now_grabcup_instance_counter_ = grabcup_instance_counter_;
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    RCLCPP_INFO(aider_node->get_logger(), "主节点已共享！");//在grapcup动作库中传递大脑节点
    locate_object_center_ = std::make_shared<LocateCenterPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建定位物体中心点动作基元
    single_arm_move_to_ = std::make_shared<SingleArmMoveToPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建单手臂运动动作基元
}

void GrapCupTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "杯子抓取任务已开启！");
    //对获取物品中心坐标点动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "object_name", std::string("cup"));
    //执行对应动作基元
    if(locate_object_center_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"获取物品中心坐标点失败！");
        return;
    }
    //对单臂运动动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "which_arm", std::string("left_arm"));
    //执行对应动作基元
    if(single_arm_move_to_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"单臂运动至目标点失败！");
        return;
    }
}

void GrapCupTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "Stop function called.");
}

bool GrapCupTask::SetParams(std::vector<std::string> params) {
    (void)params;
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "抓水杯任务无参数输入");
    return true;
}

std::string GrapCupTask::GetTaskName() {
    return "GrapCup";
}

int GrapCupTask::GetTaskCounter() {
    return now_grabcup_instance_counter_;
}



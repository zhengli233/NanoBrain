#include "aider_core/task_lib/grab/grab.hpp"
int GrapTask::grab_instance_counter_ = 0;


GrapTask::GrapTask() {
    grab_instance_counter_++;
    now_grab_instance_counter_ = grab_instance_counter_;
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    RCLCPP_INFO(aider_node->get_logger(), "主节点已共享！");//在grap动作库中传递大脑节点
    locate_object_center_ = std::make_shared<LocateCenterPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建定位物体中心点动作基元
    single_arm_move_to_ = std::make_shared<SingleArmMoveToPrimitive>(this->GetTaskName(),this->GetTaskCounter());//创建单手臂运动动作基元
}

void GrapTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("GrapTask"), "抓取任务已开启！");
    //执行对应动作基元
    if(locate_object_center_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"获取物品中心坐标点失败！");
        return;
    }
    //执行对应动作基元
    if(single_arm_move_to_->Excute()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"单臂运动至目标点失败！");
        return;
    }
}

void GrapTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("GrapTask"), "Stop function called.");
}

bool GrapTask::SetParams(std::vector<std::string> params) {
    if (params.size() != 2) {
        RCLCPP_ERROR(rclcpp::get_logger("GrapTask"),"参数数量错误，应为2个参数：(object_name, which_arm)，收到 %zu 个", params.size());
        return false;
    }
    const std::string& object_name = params[0];
    const std::string& which_arm = params[1];
    if (which_arm != "left_arm" && which_arm != "right_arm") {
        RCLCPP_ERROR(rclcpp::get_logger("GrapTask"),"第二个参数应为 left_arm 或 right_arm，收到：%s", which_arm.c_str());
        return false;
    }
    //对获取物品中心坐标点动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "object_name", object_name);
    //对单臂运动动作基元传递参数
    param_center->SetParamValue(this->GetTaskName(),this->GetTaskCounter(), "which_arm", which_arm);
    return true;
}

std::string GrapTask::GetTaskName() {
    return "Grap";
}

int GrapTask::GetTaskCounter() {
    return now_grab_instance_counter_;
}



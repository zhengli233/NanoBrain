#include "aider_core/task_lib/carry_box/carry_box.hpp"



CarryBoxTask::CarryBoxTask(std::shared_ptr<rclcpp::Node> node)
    :node_(node){
    RCLCPP_INFO(node_->get_logger(), "主节点已共享！");//在carrybox动作库中传递大脑节点
    crouch_ = std::make_shared<CrouchPrimitive>(node_);//创建下蹲动作基元
}

void CarryBoxTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("CarryBoxTask"), "箱子搬运抓取任务已开启！");
    //对下蹲动作基元传递参数
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






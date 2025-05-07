/*
1：包含头文件；
2：初始化ros2；
3：自定义节点类；
3-1创建消息发布方；
3-2创建定时器；
3-3组织并发布消息；
4:调用spin函数，并传入自定义类对象指针；
5:释放资源；
 */
#include "aider_core.hpp"
#include "aider_global_node.hpp"
#include "aider_core/task_lib/grab_cup/grab_cup.hpp"
#include "aider_core/task_lib/carry_box/carry_box.hpp"


Aider::Aider(){
  RCLCPP_INFO(aider_node->get_logger(), "发布节点创建！");
}

void Aider::Grab_Task_test(){
  grab_task_ = std::make_shared<GrapCupTask>();
  if(grab_task_) {
    grab_task_->Excute();
  } else {
    RCLCPP_ERROR(aider_node->get_logger(), "Failed to create GrabCupTask!");
  }

}

void Aider::Carry_Box_test(){
  carry_task_ = std::make_shared<CarryBoxTask>();
  if(carry_task_) {
    carry_task_->Excute();
  } else {
    RCLCPP_ERROR(aider_node->get_logger(), "Failed to create CarryBoxTask!");
  }

}




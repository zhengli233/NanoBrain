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
#include "aider_core/task_lib/grab_cup/grab_cup.hpp"


Aider::Aider() : Node("aider_core_node_cpp"){
  RCLCPP_INFO(this->get_logger(), "发布节点创建！");
}

void Aider::Task_test(){
  grab_task_ = std::make_shared<GrapCupTask>(shared_from_this());
  if(grab_task_) {
    grab_task_->Excute();
  } else {
    RCLCPP_ERROR(this->get_logger(), "Failed to create GrabCupTask!");
  }

}




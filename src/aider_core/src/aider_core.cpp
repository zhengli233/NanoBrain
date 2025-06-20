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


Aider::Aider() {
    aider_node = AiderNode::get_instance();
}

void Aider::AddTask(const std::string& name) {
    if (auto task = TaskFactory::Create(name); task) {
    queue_.emplace(task);
    } else {
    std::cerr << "Unknown task name: " << name << std::endl;
    RCLCPP_ERROR(aider_node->get_logger(), "Unknown task name:%s",name.c_str());
    }
}

void Aider::Execute() {
        while (!queue_.empty()) {
        std::shared_ptr<Task>& task_excute = queue_.front();
        task_excute->Excute();
        queue_.pop();
    }
}






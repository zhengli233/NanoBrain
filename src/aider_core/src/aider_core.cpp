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

void Aider::AddUnit(const std::string& name) {
    if (auto task = TaskFactory::Create(name); task) {
    queue_.emplace(task);
    } else if (auto primitive = PrimitiveFactory::Create(name); primitive) {
    queue_.emplace(primitive);
    } else {
    std::cerr << "Unknown unit name: " << name << std::endl;
    RCLCPP_ERROR(aider_node->get_logger(), "Unknown unit name:%s",name.c_str());
    }
}

void Aider::Execute() {
        while (!queue_.empty()) {
        Unit& unit = queue_.front();
        std::visit([](auto& ptr) {
            using T = std::decay_t<decltype(*ptr)>;
            if constexpr (std::is_base_of_v<Task, T>) {
                ptr->Excute();
            } else if constexpr (std::is_base_of_v<Primitive, T>) {
                ptr->Excute();
            }
        }, unit);
        queue_.pop();
    }
}






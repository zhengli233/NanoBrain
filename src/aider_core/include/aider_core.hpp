#ifndef AIDER_CORE_HPP_
#define AIDER_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include <queue>
#include <variant>
#include <memory>
#include <string>
#include <iostream>
#include "aider_core/task_lib/task.hpp"
#include "aider_global_node.hpp"//ros2节点单例
#include "param_global_node.hpp"//参数中心单例
#include "aider_core/primitive_lib/primitive_lib.hpp"
#include "aider_core/task_lib/task_factory.hpp"

class Aider{
public:
    Aider();
    void AddTask(const std::string& name);
    void Execute();

private:
    std::queue<std::shared_ptr<Task>> queue_;
    std::shared_ptr<rclcpp::Node> aider_node;
    
};


#endif  // AIDER_CORE_HPP_


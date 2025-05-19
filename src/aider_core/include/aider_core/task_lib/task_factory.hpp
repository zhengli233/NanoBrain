#ifndef TASK_FACTORY_HPP_
#define TASK_FACTORY_HPP_
/*任务库工厂类*/
#include <memory>
#include <string>
#include <iostream>
#include "task.hpp"
#include "aider_global_node.hpp" //节点类
#include "aider_core/task_lib/grab_cup/grab_cup.hpp"
#include "aider_core/task_lib/carry_box/carry_box.hpp"

class TaskFactory {
public:
    static std::shared_ptr<Task> Create(const std::string& name) {
        if (name == "GrabCup") {
            return std::make_shared<GrapCupTask>();
        } else if (name == "CarryBox") {
            return std::make_shared<CarryBoxTask>();
        } else {
            RCLCPP_ERROR(AiderNode::get_instance()->get_logger(), "Task not found!");
            return nullptr;
        }
    }
};


#endif /*TASK_FACTORY_HPP_*/



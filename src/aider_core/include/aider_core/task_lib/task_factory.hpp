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
#include "aider_core/task_lib/grab/grab.hpp"

class TaskFactory {
public:
    static std::shared_ptr<Task> Create(const std::string& command) {
        std::string name;
        std::vector<std::string> params;

        // 检查是否为参数化格式，如 Place(cup, table)
        size_t l = command.find('(');
        size_t r = command.find(')');

        if (l != std::string::npos && r != std::string::npos && r > l) {
            // 括号内有内容，是参数化任务
            name = command.substr(0, l);
            std::string param_str = command.substr(l + 1, r - l - 1);
            std::istringstream ss(param_str);
            std::string token;

            while (std::getline(ss, token, ',')) {
                // 去除空格
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);
                params.push_back(token);
            }
        } else {
            // 没有括号，是传统任务（如 GrabCup）
            name = command;
            params.clear();
        }
        
        std::shared_ptr<Task> task;
        if (name == "GrabCup") {
            task = std::make_shared<GrapCupTask>();
        } else if (name == "CarryBox") {
            task = std::make_shared<CarryBoxTask>();
        } else if (name == "Grap") {
            task = std::make_shared<GrapTask>();
        } else {
            RCLCPP_ERROR(AiderNode::get_instance()->get_logger(), "Unknown task: %s", name.c_str());
            return nullptr;
        }

        if (task->SetParams(params) == false) {
            RCLCPP_ERROR(AiderNode::get_instance()->get_logger(), "Task %s parameter error", name.c_str());
            return nullptr;
        }

        return task;

    }
};


#endif /*TASK_FACTORY_HPP_*/


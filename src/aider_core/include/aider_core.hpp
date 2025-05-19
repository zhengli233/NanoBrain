#ifndef AIDER_CORE_HPP_
#define AIDER_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include <queue>
#include <variant>
#include <memory>
#include <string>
#include <iostream>
#include "task.hpp"
#include "aider_global_node.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"
#include "task_factory.hpp"
#include "aider_core/primitive_lib/primitive_factory.hpp"
#include "aider_core/param_center/param_center.hpp"

class Aider{
public:
    using Unit = std::variant<std::shared_ptr<Task>, std::shared_ptr<Primitive>>;
    Aider();
    void AddUnit(const std::string& name);
    void Execute();

private:
    std::queue<Unit> queue_;
    std::shared_ptr<rclcpp::Node> aider_node;
    
};


#endif  // AIDER_CORE_HPP_


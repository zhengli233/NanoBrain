#ifndef AIDER_CORE_HPP_
#define AIDER_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include <queue>
#include <variant>
#include <memory>
#include <string>
#include <iostream>
#include "task.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"
#include "task_factory.hpp"
#include "aider_core/primitive_lib/primitive_factory.hpp"

class Aider{
public:
    using Unit = std::variant<std::shared_ptr<Task>, std::shared_ptr<Primitive>>;
    void AddUnit(const std::string& name);
    void Execute();

private:
    std::queue<Unit> queue_;
    
};


#endif  // AIDER_CORE_HPP_


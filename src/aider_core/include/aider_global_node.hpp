#ifndef AIDER_GLOBAL_CORE_HPP_
#define AIDER_GLOBAL_CORE_HPP_
//设置一个规划节点的单例，避免了节点传递的繁琐
#include <memory>
#include "rclcpp/rclcpp.hpp"

// 声明一个全局的共享指针
extern std::shared_ptr<rclcpp::Node> aider_node;




#endif  // AIDER_GLOBAL_CORE_HPP_



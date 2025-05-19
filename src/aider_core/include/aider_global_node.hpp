#ifndef AIDER_GLOBAL_CORE_HPP_
#define AIDER_GLOBAL_CORE_HPP_


#include <memory>
#include "rclcpp/rclcpp.hpp"

class AiderNode {
public:
    static std::shared_ptr<rclcpp::Node> get_instance();

private:
    AiderNode() = default;
    static std::shared_ptr<rclcpp::Node> instance_;
};




#endif  // AIDER_GLOBAL_CORE_HPP_



#include "aider_global_node.hpp"

std::shared_ptr<rclcpp::Node> AiderNode::instance_ = nullptr;

std::shared_ptr<rclcpp::Node> AiderNode::get_instance() {
    if (instance_ == nullptr) {
        instance_ = std::make_shared<rclcpp::Node>("aider_core_node_cpp");
    }
    return instance_;
}

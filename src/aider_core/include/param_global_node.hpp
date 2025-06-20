#ifndef PARAM_GLOBAL_CORE_HPP_
#define PARAM_GLOBAL_CORE_HPP_


#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "aider_core/param_center/param_center.hpp"

class ParamNode {
public:
    static std::shared_ptr<ParamCenter> get_instance(const std::string& yaml_path);

private:
    ParamNode() = default;
    static std::shared_ptr<ParamCenter> instance_;
};




#endif  // PARAM_GLOBAL_CORE_HPP_



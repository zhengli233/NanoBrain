#ifndef PARAM_CENTER_HPP_
#define PARAM_CENTER_HPP_


#include "param.hpp"
#include <unordered_map>
#include <string>
#include <optional>
#include "aider_global_node.hpp"
#include <any>
#include <thread>
#include <chrono>


class ParamCenter {
public:
    explicit ParamCenter(const std::string& yaml_path);
    bool assignParam(const std::string& name, const std::any& value);
    std::optional<std::any> getParamValue(const std::string& name);
    bool clear_param(const std::string& name);
    // void clearPrimitiveParams();  // 删除所有primitive参数的赋值状态
    // void clearTaskParams();       // 删除所有task参数的赋值状态

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::unordered_map<std::string, Param> param_table_;
    void param_center_handle();
};






#endif  // PARAM_CENTER_HPP_




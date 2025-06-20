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
#include "task.hpp"
#include "rclcpp/exceptions.hpp"

class ParamCenter {
public:
    explicit ParamCenter(const std::string& yaml_path);
    std::string GetParamType(const std::string& name);//通过查表获取参数的类型
    bool RegistParam(const std::string& task_name, int instance_id, const std::string& key);
    bool SetParamValue(const std::string& task_name, int instance_id, const std::string& key, const std::any& value);
    bool SetParamByUser(const std::string& task_name, int instance_id, const std::string& key);
    std::optional<std::any> GetParamValue(const std::string& task_name, int instance_id, const std::string& key);
private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::unordered_map<std::string, Param> param_table_;
};






#endif  // PARAM_CENTER_HPP_




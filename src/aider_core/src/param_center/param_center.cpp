#include "aider_core/param_center/param_center.hpp"
#include <yaml-cpp/yaml.h>
#include <iostream>

// 构造函数：加载 YAML 参数文件
ParamCenter::ParamCenter(const std::string& yaml_path) {
    aider_node = AiderNode::get_instance();
    try {
        YAML::Node config = YAML::LoadFile(yaml_path);
        YAML::Node params_node = config["parameters"];

        for (auto it = params_node.begin(); it != params_node.end(); ++it) {
            std::string name = it->first.as<std::string>();
            std::string type_str = it->second["type"].as<std::string>();
            std::string scope_str = it->second["scope"].as<std::string>();

            try {
                ParamType type = parseType(type_str);
                ParamScope scope = parseScope(scope_str);

                Param param;
                param.name = name;
                param.type = type;
                param.scope = scope;
                param.is_assigned = false;

                param_table_[name] = param;

            } catch (const std::exception& e) {
                RCLCPP_ERROR(aider_node->get_logger(), "参数%s解析失败",name.c_str());
            }
        }
        RCLCPP_INFO(aider_node->get_logger(), "参数解析成功！！！");


    } catch (const YAML::Exception& e) {
        RCLCPP_ERROR(aider_node->get_logger(), "YAML 加载失败");
    }
    std::thread(&ParamCenter::param_center_handle, this).detach();
}


void ParamCenter::param_center_handle() {
    rclcpp::Rate rate(100);
    while (rclcpp::ok()) {
    
    rate.sleep(); 
    }
}


bool ParamCenter::assignParam(const std::string& name, const std::any& value) {
    auto it = param_table_.find(name);
    if (it == param_table_.end()) {
        RCLCPP_ERROR(aider_node->get_logger(), "assignParam 错误：未找到参数%s",name.c_str());
        return false;
    }

    Param& param = it->second;

    // 先判断value的类型是否与param.type匹配
    bool type_match = false;

    try {
        switch (param.type) {
            case ParamType::INT:
                type_match = value.type() == typeid(int);
                break;
            case ParamType::FLOAT:
                type_match = value.type() == typeid(float);
                break;
            case ParamType::STRING:
                type_match = value.type() == typeid(std::string);
                break;
            case ParamType::BOOL:
                type_match = value.type() == typeid(bool);
                break;
            default:
                RCLCPP_ERROR(aider_node->get_logger(), "assignParam 错误：参数类型未知");
                return false;
        }
    } catch (...) {
        RCLCPP_ERROR(aider_node->get_logger(), "assignParam 类型判断异常");
        return false;
    }

    if (!type_match) {
        RCLCPP_ERROR(aider_node->get_logger(), "assignParam 错误：参数 %s 赋值类型不匹配",name.c_str());
        return false;
    }

    // 赋值
    param.value = value;
    param.is_assigned = true;

    return true;
}


std::optional<std::any> ParamCenter::getParamValue(const std::string& name) {
    auto it = param_table_.find(name);
    if (it == param_table_.end()) {
        RCLCPP_ERROR(aider_node->get_logger(), "参数不存在: %s",name.c_str());
        return std::nullopt;
    }

    Param& param = it->second;

    if (param.is_assigned) {
        return param.value;
    }

    while (true) {
        RCLCPP_INFO(aider_node->get_logger(), "请输入参数 [%s] 的值 (类型: %s):",name.c_str(), paramTypeToString(param.type).c_str());
        bool input_valid = false;
        switch (param.type) {
            case ParamType::INT: {
                int val;
                std::cin >> val;
                if (!std::cin.fail()) {
                    param.value = val;
                    input_valid = true;
                }
                break;
            }
            case ParamType::FLOAT: {
                float val;
                std::cin >> val;
                if (!std::cin.fail()) {
                    param.value = val;
                    input_valid = true;
                }
                break;
            }
            case ParamType::STRING: {
                std::string val;
                std::cin >> val;
                if (!val.empty()) {
                    param.value = val;
                    input_valid = true;
                }
                break;
            }
            case ParamType::BOOL: {
                bool val;
                std::cin >> val;
                if (!std::cin.fail()) {
                    param.value = val;
                    input_valid = true;
                }
                break;
            }
            default:
                RCLCPP_ERROR(aider_node->get_logger(), "未知参数类型，无法输入");
                return std::nullopt;
        }

        if (input_valid) {
            param.is_assigned = true;
            param.request_count++;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除多余输入
            return param.value;
        } else {
            RCLCPP_ERROR(aider_node->get_logger(), "输入格式错误，请重新输入！");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool ParamCenter::clear_param(const std::string& name) {
    auto it = param_table_.find(name);
    if (it == param_table_.end()) {
        return false;  // 没找到该参数
    }

    Param& param = it->second;
    param.value.reset();             // 清除值（std::any 没有 reset，但我们可以这样重置）
    param.value = std::any();        // 重新置空
    param.is_assigned = false;       // 标记为未赋值
    param.request_count = 0;          // 清除调用次数

    return true;
}



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

            try {
                ParamType type = parseType(type_str);

                Param param;
                param.name = name;
                param.type = type;

                param_table_[name] = param;

            } catch (const std::exception& e) {
                RCLCPP_ERROR(aider_node->get_logger(), "参数%s解析失败",name.c_str());
            }
        }
        RCLCPP_INFO(aider_node->get_logger(), "参数解析成功！！！");


    } catch (const YAML::Exception& e) {
        RCLCPP_ERROR(aider_node->get_logger(), "YAML 加载失败");
    }
}

std::string ParamCenter::GetParamType(const std::string& name) {
    auto it = param_table_.find(name);
    if (it != param_table_.end()) {
        return paramTypeToString(it->second.type);
    } else {
        RCLCPP_WARN(aider_node->get_logger(), "参数 '%s' 不存在于 param_table_", name.c_str());
        return "unknown";
    }
}

bool ParamCenter::RegistParam(const std::string& task_name, int instance_id, const std::string& key) {
    std::string full_name = task_name + std::to_string(instance_id) + "_" + key;
    std::string type_str = GetParamType(key);

    try {
        if (type_str == "int") {
            aider_node->declare_parameter<int>(full_name, 0);
        } else if (type_str == "float") {
            aider_node->declare_parameter<double>(full_name, 0.0);
        } else if (type_str == "string") {
            aider_node->declare_parameter<std::string>(full_name, "");
        } else if (type_str == "bool") {
            aider_node->declare_parameter<bool>(full_name, false);
        } else {
            RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型未知，注册失败", full_name.c_str());
            return false;
        }
    } catch (const rclcpp::exceptions::ParameterAlreadyDeclaredException& e) {
        RCLCPP_DEBUG(aider_node->get_logger(), "参数 [%s] 已注册，跳过", full_name.c_str());
    }

    RCLCPP_INFO(aider_node->get_logger(), "注册参数 [%s] 成功", full_name.c_str());
    return true;
}

bool ParamCenter::SetParamValue(const std::string& task_name, int instance_id, const std::string& key, const std::any& value) {
    std::string full_name = task_name + std::to_string(instance_id) + "_" + key;
    std::string type_str = GetParamType(key);

    try {
        if (type_str == "int") {
            if (!value.has_value() || value.type() != typeid(int)) {
                RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型与传入值不匹配", full_name.c_str());
                return false;
            }
            int val = std::any_cast<int>(value);
            aider_node->set_parameter(rclcpp::Parameter(full_name, val));
        } else if (type_str == "float") {
            if (!value.has_value() || (value.type() != typeid(float) && value.type() != typeid(double))) {
                RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型与传入值不匹配", full_name.c_str());
                return false;
            }
            double val = (value.type() == typeid(float)) ?
                        static_cast<double>(std::any_cast<float>(value)) :
                        std::any_cast<double>(value);
            aider_node->set_parameter(rclcpp::Parameter(full_name, val));
        } else if (type_str == "string") {
            if (!value.has_value() || value.type() != typeid(std::string)) {
                RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型与传入值不匹配", full_name.c_str());
                return false;
            }
            std::string val = std::any_cast<std::string>(value);
            aider_node->set_parameter(rclcpp::Parameter(full_name, val));
        } else if (type_str == "bool") {
            if (!value.has_value() || value.type() != typeid(bool)) {
                RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型与传入值不匹配", full_name.c_str());
                return false;
            }
            bool val = std::any_cast<bool>(value);
            aider_node->set_parameter(rclcpp::Parameter(full_name, val));
        } else {
            RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型未知，无法设置值", full_name.c_str());
            return false;
        }
    } catch (const std::bad_any_cast& e) {
        RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 设置值时类型转换失败", full_name.c_str());
        return false;
    }

    RCLCPP_INFO(aider_node->get_logger(), "参数 [%s] 设置值成功", full_name.c_str());
    return true;
}


bool ParamCenter::SetParamByUser(const std::string& task_name, int instance_id, const std::string& key) {
    std::string full_name = task_name + std::to_string(instance_id) + "_" + key;

    std::string type_str = GetParamType(key);
    if (type_str == "unknown") {
        RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 类型未知，无法输入赋值", full_name.c_str());
        return false;
    }

    std::any value;
    while (true) {
        std::cout << "请输入参数 [" << full_name << "]，类型为 [" << type_str << "]: ";

        std::string input;
        std::getline(std::cin, input);

        try {
            if (type_str == "int") {
                int val = std::stoi(input);
                value = val;
                break;
            } else if (type_str == "float") {
                double val = std::stod(input);
                value = val;
                break;
            } else if (type_str == "bool") {
                if (input == "true" || input == "1") {
                    value = true;
                } else if (input == "false" || input == "0") {
                    value = false;
                } else {
                    throw std::invalid_argument("bool 输入无效");
                }
                break;
            } else if (type_str == "string") {
                value = input;
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "输入格式错误，请重新输入！" << std::endl;
        }
    }

    return SetParamValue(task_name, instance_id, key, value);
}


std::optional<std::any> ParamCenter::GetParamValue(const std::string& task_name, int instance_id, const std::string& key) {
    std::string full_key = task_name + std::to_string(instance_id) + "_" + key;

    auto it = param_table_.find(key);
    if (it == param_table_.end()) {
        RCLCPP_WARN(aider_node->get_logger(), "参数 [%s] 未在参数表中注册，读取失败", key.c_str());
        return std::nullopt;
    }

    ParamType type = it->second.type;

    try {
        if (type == ParamType::INT) {
            return aider_node->get_parameter(full_key).as_int();
        } else if (type == ParamType::FLOAT) {
            return aider_node->get_parameter(full_key).as_double();
        } else if (type == ParamType::STRING) {
            return aider_node->get_parameter(full_key).as_string();
        } else if (type == ParamType::BOOL) {
            return aider_node->get_parameter(full_key).as_bool();
        } else {
            RCLCPP_ERROR(aider_node->get_logger(), "不支持的参数类型 [%s]", full_key.c_str());
            return std::nullopt;
        }
    } catch (const rclcpp::exceptions::ParameterNotDeclaredException& e) {
        RCLCPP_ERROR(aider_node->get_logger(), "参数 [%s] 尚未声明", full_key.c_str());
        return std::nullopt;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(aider_node->get_logger(), "读取参数 [%s] 出错: %s", full_key.c_str(), e.what());
        return std::nullopt;
    }
}



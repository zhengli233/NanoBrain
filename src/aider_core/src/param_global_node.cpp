#include "param_global_node.hpp"

std::shared_ptr<ParamCenter> ParamNode::instance_ = nullptr;

std::shared_ptr<ParamCenter> ParamNode::get_instance(const std::string& yaml_path) {
    if (instance_ == nullptr) {
        instance_ = std::make_shared<ParamCenter>(yaml_path);//初始化参数中心，加载用户参数配置文件
    }
    return instance_;
}

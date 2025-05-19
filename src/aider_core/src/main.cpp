#include "aider_core.hpp"
#include "aider_global_node.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto param_center = std::make_shared<ParamCenter>("src/aider_core/config/parameters.yaml");//初始化参数中心，加载用户参数配置文件
    auto aider_node = AiderNode::get_instance();
    auto aider = std::make_shared<Aider>();
    aider->AddUnit("CarryBox");
    aider->Execute();
    rclcpp::spin(aider_node);
    rclcpp::shutdown();
    return 0;
}


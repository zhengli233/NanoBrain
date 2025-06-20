#include "aider_core.hpp"
#include "aider_global_node.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    auto aider_node = AiderNode::get_instance();
    auto aider = std::make_shared<Aider>();
    aider->AddTask("CarryBox");
    aider->Execute();
    rclcpp::spin(aider_node);
    rclcpp::shutdown();
    return 0;
}


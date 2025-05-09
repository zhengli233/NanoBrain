#include "aider_core.hpp"
#include "aider_global_node.hpp"

std::shared_ptr<rclcpp::Node> aider_node = nullptr;

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    aider_node = std::make_shared<rclcpp::Node>("aider_core_node_cpp");
    auto aider = std::make_shared<Aider>();
    aider->AddUnit("GrabCup");
    aider->Execute();
    rclcpp::spin(aider_node);
    rclcpp::shutdown();
    return 0;
}



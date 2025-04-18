#include "aider_core.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto aider = std::make_shared<Aider>();
    aider->Carry_Box_test();
    rclcpp::spin(aider);
    rclcpp::shutdown();
    return 0;
}



#ifndef LOCATE_OBJECT_RL_HPP_
#define LOCATE_OBJECT_RL_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "vision_interfaces/srv/locate_object_rl.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using vision_interfaces::srv::LocateObjectRL;


class LocateRLPrimitive : public Primitive {
public:
    explicit LocateRLPrimitive();
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<Client> rl_ask_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    std::string object_label;
    double left_target_orientation_x;
    double left_target_orientation_y;
    double left_target_orientation_z;
    double left_target_orientation_w;
    double left_target_position_x;
    double left_target_position_y;
    double left_target_position_z;
    double right_target_orientation_x;
    double right_target_orientation_y;
    double right_target_orientation_z;
    double right_target_orientation_w;
    double right_target_position_x;
    double right_target_position_y;
    double right_target_position_z;
};







#endif  // LOCATE_OBJECT_RL_HPP_



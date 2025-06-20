#ifndef SINGLE_ARM_MOVE_TO_HPP_
#define SINGLE_ARM_MOVE_TO_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "arm_interfaces/srv/single_arm_move.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using arm_interfaces::srv::SingleArmMove;


class SingleArmMoveToPrimitive : public Primitive {
public:
    explicit SingleArmMoveToPrimitive(std::string task_name,int task_instance_id);
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    std::shared_ptr<Client> single_arm_move_to_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    std::string which_arm;
    double target_orientation_x;
    double target_orientation_y;
    double target_orientation_z;
    double target_orientation_w;
    double target_position_x;
    double target_position_y;
    double target_position_z;
    };







#endif  // SINGLE_ARM_MOVE_TO_HPP_

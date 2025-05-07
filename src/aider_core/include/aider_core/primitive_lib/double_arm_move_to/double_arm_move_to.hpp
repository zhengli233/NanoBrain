#ifndef DOUBLE_ARM_MOVE_TO_HPP_
#define DOUBLE_ARM_MOVE_TO_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "arm_interfaces/srv/double_arm_move.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using arm_interfaces::srv::DoubleArmMove;


class DoubleArmMovePrimitive : public Primitive {
    public:
        explicit DoubleArmMovePrimitive();
        virtual bool Excute();
        virtual void Stop();

    private:
        std::shared_ptr<Client> double_arm_move_to_client_;//设置服务通信客户端
        //以下是本动作基元所需变量
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







#endif  // DOUBLE_ARM_MOVE_TO_HPP_



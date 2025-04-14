#ifndef GRAB_CUP_HPP_
#define GRAB_CUP_HPP_
#include "task.hpp"
#include "vision_interfaces/srv/locate_object_center.hpp"
#include "arm_interfaces/srv/single_arm_move.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using vision_interfaces::srv::LocateObjectCenter;
using arm_interfaces::srv::SingleArmMove;


class GrapCupTask : public Task {
    public:
        explicit GrapCupTask(std::shared_ptr<rclcpp::Node> node);
        virtual void Excute();
        virtual void Stop();

    private:
        std::shared_ptr<rclcpp::Node> node_;
        std::shared_ptr<Client> center_ask_client_;
        std::shared_ptr<Client> single_arm_move_client_;
    };







#endif  // GRAB_CUP_HPP_


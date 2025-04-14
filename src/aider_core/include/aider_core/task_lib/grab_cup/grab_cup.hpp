#ifndef GRAB_CUP_HPP_
#define GRAB_CUP_HPP_
#include "../task.hpp"
#include "aider_core/primitive_lib/locate_object_center/locate_object_center.hpp"
#include "aider_core/primitive_lib/single_arm_move_to/single_arm_move_to.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"




class GrapCupTask : public Task {
    public:
        explicit GrapCupTask(std::shared_ptr<rclcpp::Node> node);
        virtual void Excute();
        virtual void Stop();

    private:
        std::shared_ptr<rclcpp::Node> node_;
        std::shared_ptr<Primitive> locate_object_center_;
        std::shared_ptr<Primitive> single_arm_move_to_;
    };







#endif  // GRAB_CUP_HPP_


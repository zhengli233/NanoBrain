#ifndef CARRY_BOX_HPP_
#define CARRY_BOX_HPP_
#include "../task.hpp"
#include "aider_core/primitive_lib/crouch/crouch.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"




class CarryBoxTask : public Task {
    public:
        explicit CarryBoxTask(std::shared_ptr<rclcpp::Node> node);
        virtual void Excute();
        virtual void Stop();

    private:
        std::shared_ptr<rclcpp::Node> node_;
        std::shared_ptr<Primitive> crouch_;
    };







#endif  // CARRY_BOX_HPP_


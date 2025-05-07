#ifndef CARRY_BOX_HPP_
#define CARRY_BOX_HPP_
#include "../task.hpp"
#include "aider_global_node.hpp"
#include "aider_core/primitive_lib/crouch/crouch.hpp"
#include "aider_core/primitive_lib/double_arm_move_to/double_arm_move_to.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"




class CarryBoxTask : public Task {
    public:
        explicit CarryBoxTask();
        virtual void Excute();
        virtual void Stop();

    private:
        std::shared_ptr<Primitive> crouch_;
        std::shared_ptr<Primitive> double_arm_move_to_;
    };







#endif  // CARRY_BOX_HPP_


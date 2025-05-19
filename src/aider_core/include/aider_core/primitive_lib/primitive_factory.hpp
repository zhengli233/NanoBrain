#ifndef PRIMITIVE_FACTORY_HPP_
#define PRIMITIVE_FACTORY_HPP_
/*动作基元库工厂类*/
#include <memory>
#include <string>
#include <iostream>
#include "aider_global_node.hpp"//节点类
#include "primitive_lib.hpp" 
#include "aider_core/primitive_lib/crouch/crouch.hpp"
#include "aider_core/primitive_lib/double_arm_move_to/double_arm_move_to.hpp"
#include "aider_core/primitive_lib/locate_object_center/locate_object_center.hpp"
#include "aider_core/primitive_lib/locate_object_rl/locate_object_rl.hpp"
#include "aider_core/primitive_lib/single_arm_move_to/single_arm_move_to.hpp"

class PrimitiveFactory {
public:
    static std::shared_ptr<Primitive> Create(const std::string& name) {
        if (name == "Crouch") {
            return std::make_shared<CrouchPrimitive>();
        } else if (name == "DoubleArmMoveTo") {
            return std::make_shared<DoubleArmMovePrimitive>();
        } else if (name == "LocateObjectCenter") {
            return std::make_shared<LocateCenterPrimitive>();
        } else if (name == "LocateObjectCenterRL") {
            return std::make_shared<LocateRLPrimitive>();
        } else if (name == "SingleArmMoveTo") {
            return std::make_shared<SingleArmMoveToPrimitive>();
        } else {
            RCLCPP_ERROR(AiderNode::get_instance()->get_logger(), "Primitive not found!");
            return nullptr;
        }
    }
};


#endif /*PRIMITIVE_FACTORY_HPP_*/




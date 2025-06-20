#ifndef CARRY_BOX_HPP_
#define CARRY_BOX_HPP_
#include "../task.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "aider_core/primitive_lib/crouch/crouch.hpp"
#include "aider_core/primitive_lib/double_arm_move_to_cartesian/double_arm_move_to_cartesian.hpp"
#include "aider_core/primitive_lib/nav_to_object/nav_to_object.hpp"
#include "aider_core/primitive_lib/nav_retreat_roate/nav_retreat_roate.hpp"
#include "aider_core/primitive_lib/nav_to_point/nav_to_point.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"




class CarryBoxTask : public Task {
public:
    explicit CarryBoxTask();
    virtual void Excute();
    virtual void Stop();
    virtual bool SetParams(std::vector<std::string> params);
    virtual std::string GetTaskName();
    virtual int GetTaskCounter();
private:
    std::shared_ptr<Primitive> nav_to_object_;
    std::shared_ptr<Primitive> nav_retreat_roate_;
    std::shared_ptr<Primitive> nav_to_point_;
    std::shared_ptr<Primitive> crouch_;
    std::shared_ptr<Primitive> crouch_1_;
    std::shared_ptr<Primitive> double_arm_move_to_cartesian_;
    std::shared_ptr<Primitive> double_arm_move_to_cartesian_1_;
    std::shared_ptr<Primitive> double_arm_move_to_cartesian_2_;
    std::shared_ptr<Primitive> double_arm_move_to_cartesian_3_;
    std::shared_ptr<Primitive> double_arm_move_to_cartesian_4_;
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    int now_carrybox_instance_counter_;//本次任务计数
    static int carrybox_instance_counter_; //任务生成计数器
};







#endif  // CARRY_BOX_HPP_


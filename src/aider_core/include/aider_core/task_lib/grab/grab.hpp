#ifndef GRAB_HPP_
#define GRAB_HPP_
#include "../task.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "aider_core/primitive_lib/locate_object_center/locate_object_center.hpp"
#include "aider_core/primitive_lib/single_arm_move_to/single_arm_move_to.hpp"
#include "aider_core/primitive_lib/primitive_lib.hpp"




class GrapTask : public Task {
public:
    explicit GrapTask();
    virtual void Excute();
    virtual void Stop();
    virtual bool SetParams(std::vector<std::string> params);
    virtual std::string GetTaskName();
    virtual int GetTaskCounter();
private:
    std::shared_ptr<Primitive> locate_object_center_;
    std::shared_ptr<Primitive> single_arm_move_to_;
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    int now_grab_instance_counter_;//本次任务计数
    static int grab_instance_counter_; //任务生成计数器
};







#endif  // GRAB_HPP_


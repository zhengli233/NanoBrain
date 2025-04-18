#ifndef AIDER_CORE__AIDER_CORE_HPP_
#define AIDER_CORE__AIDER_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "task.hpp"

class Aider: public rclcpp::Node{
    public:
        Aider();  // 构造函数声明
        void Grab_Task_test();//测试抓取的程序逻辑
        void Carry_Box_test();//测试搬运箱子程序逻辑
    private:
        std::shared_ptr<Task> grab_task_;
        std::shared_ptr<Task> carry_task_;

    
    };


#endif  // AIDER_CORE__AIDER_CORE_HPP_


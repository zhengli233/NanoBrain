#ifndef TASK_HPP_
#define TASK_HPP_

#include "rclcpp/rclcpp.hpp"

class Task {
    public:
        virtual void Excute() = 0;
        virtual void Stop() = 0;
    };











#endif // TASK_HPP_
#ifndef TASK_HPP_
#define TASK_HPP_

#include "rclcpp/rclcpp.hpp"

class Task {
public:
    virtual void Excute() = 0;
    virtual void Stop() = 0;
    virtual bool SetParams(std::vector<std::string> params) = 0;
    virtual std::string GetTaskName() = 0;
    virtual int GetTaskCounter() = 0;
};











#endif // TASK_HPP_
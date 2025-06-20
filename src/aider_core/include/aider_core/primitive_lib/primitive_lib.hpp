#ifndef PRIMITIVE_LIB_HPP_
#define PRIMITIVE_LIB_HPP_

#include "rclcpp/rclcpp.hpp"
#include <string>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <utility>

class Primitive {
public:
    virtual bool Excute() = 0;
    virtual void Stop() = 0;
    std::string task_name_;
    int task_instance_id_;
};











#endif // PRIMITIVE_LIB_HPP_
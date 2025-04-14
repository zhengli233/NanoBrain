#ifndef CLIENT_SERVICE_HPP
#define CLIENT_SERVICE_HPP

#include "rclcpp/rclcpp.hpp"
#include <functional>

class Client {
public:
    virtual ~Client() = default;

    //创建服务通讯客户端
    virtual void Create(const std::string& service_name) = 0;
    // 连接服务（纯虚函数，必须由子类实现）
    virtual bool Connect() = 0;
    // 发送请求服务（纯虚函数，必须由子类实现）
    virtual bool SendRequest(const void* request, void* output) = 0;

};

#endif // CLIENT_SERVICE_HPP


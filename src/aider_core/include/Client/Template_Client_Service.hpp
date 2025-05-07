// Template_Client_Service.hpp
#ifndef TEMPLATE_CLIENT_SERVICE_HPP
#define TEMPLATE_CLIENT_SERVICE_HPP

#include "Client.hpp"
#include "aider_global_node.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

template<typename ServiceT>
class TemplateClientService : public Client {
public:
    using Request = typename ServiceT::Request;
    using Response = typename ServiceT::Response;

    explicit TemplateClientService() 
    :client_(nullptr) {}

    // 实现基类创建服务的方法
    void Create(const std::string& service_name) override {
        client_ = aider_node->create_client<ServiceT>(service_name);
    }
    // 实现基类连接服务的方法
    bool Connect() override {
        while(!client_->wait_for_service(2s))
        {
            //需要对control_c是否按下，按下后如何处理。
            if(!rclcpp::ok())
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强行终止客户端！");
                return false;
            }
            RCLCPP_INFO(aider_node->get_logger(),"服务连接中！");
        }
        return true;//如果连接成功返回true，否则返回false。
    }

    bool SendRequest(const void* request, void* output) {
        // 参数类型检查
        if (!request || !output) {
            RCLCPP_ERROR(aider_node->get_logger(), "缺少请求与输出！");
            return false;
        }
        // 类型转换
        const Request* concrete_request = static_cast<const Request*>(request);
        Response* concrete_output = static_cast<Response*>(output);
        // 发送请求
        auto future = client_->async_send_request(std::make_shared<Request>(*concrete_request));
        // 阻塞等待响应
        auto result = rclcpp::spin_until_future_complete(aider_node->get_node_base_interface(),future);
        // 处理结果
        if (result == rclcpp::FutureReturnCode::SUCCESS) {
            *concrete_output = *future.get();
            return true;
        }
        RCLCPP_ERROR(aider_node->get_logger(), "服务端返回失败 (错误码: %d)", static_cast<int>(result));
        return false;
    }



private:
    typename rclcpp::Client<ServiceT>::SharedPtr client_;
};

#endif // TEMPLATE_CLIENT_SERVICE_HPP
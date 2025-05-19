#ifndef CROUCH_HPP_
#define CROUCH_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "lowerbody_interfaces/srv/crouch.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using lowerbody_interfaces::srv::Crouch;


class CrouchPrimitive : public Primitive {
public:
    explicit CrouchPrimitive();
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<Client> crouch_to_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    double crouch_height;
};







#endif  // CROUCH_HPP_

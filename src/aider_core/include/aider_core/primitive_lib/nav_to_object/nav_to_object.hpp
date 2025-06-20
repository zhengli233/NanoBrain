#ifndef NAV_TO_OBJECT_HPP_
#define NAV_TO_OBJECT_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "nav_interfaces/srv/nav_to_object.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using nav_interfaces::srv::NavToObject;


class NavToObjectPrimitive : public Primitive {
public:
    explicit NavToObjectPrimitive(std::string task_name,int task_instance_id);
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    std::shared_ptr<Client> nav_to_object_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    std::string object_label;
};







#endif  // NAV_TO_OBJECT_HPP_

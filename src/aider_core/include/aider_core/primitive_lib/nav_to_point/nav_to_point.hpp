#ifndef NAV_TO_POINT_HPP_
#define NAV_TO_POINT_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "nav_interfaces/srv/nav_to_point.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using nav_interfaces::srv::NavToPoint;


class NavToPointPrimitive : public Primitive {
public:
    explicit NavToPointPrimitive(std::string task_name,int task_instance_id);
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    std::shared_ptr<Client> nav_to_point_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    double nav_to_target_x;
    double nav_to_target_y;
    double nav_to_target_oriention_x;
    double nav_to_target_oriention_y;
    double nav_to_target_oriention_z;
    double nav_to_target_oriention_w;
};







#endif  // NAV_TO_POINT_HPP_

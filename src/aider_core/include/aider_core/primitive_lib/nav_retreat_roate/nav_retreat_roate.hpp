#ifndef NAV_RETREAT_ROATE_HPP_
#define NAV_RETREAT_ROATE_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "param_global_node.hpp"//参数中心单例
#include "nav_interfaces/srv/nav_carry_box_retreaat_and_roate.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using nav_interfaces::srv::NavCarryBoxRetreaatAndRoate;


class NavCarryBoxRetreaatAndRoatePrimitive : public Primitive {
public:
    explicit NavCarryBoxRetreaatAndRoatePrimitive(std::string task_name,int task_instance_id);
    virtual bool Excute();
    virtual void Stop();

private:
    std::shared_ptr<rclcpp::Node> aider_node;
    std::shared_ptr<ParamCenter> param_center; 
    std::shared_ptr<Client> nav_retreat_roate_client_;//设置服务通信客户端
    //以下是本动作基元所需变量
    bool start_flag;
};







#endif  // NAV_RETREAT_ROATE_HPP_

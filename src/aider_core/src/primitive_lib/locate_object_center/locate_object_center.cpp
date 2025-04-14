#include "aider_core/primitive_lib/locate_object_center/locate_object_center.hpp"

using vision_interfaces::srv::LocateObjectCenter;
using namespace std::chrono_literals;


LocateCenterPrimitive::LocateCenterPrimitive(std::shared_ptr<rclcpp::Node> node)
    :node_(node){
    RCLCPP_INFO(node_->get_logger(), "动作基元：定位物体坐标点已激活！");//在LocateCenterPrimitive动作基元库中传递大脑节点
    //初始化参数列表
    REGISTER_PARAM("object_label", std::string, object_label);
    REGISTER_PARAM("target_orientation_x", double, target_orientation_x);
    REGISTER_PARAM("target_orientation_y", double, target_orientation_y);
    REGISTER_PARAM("target_orientation_z", double, target_orientation_z);
    REGISTER_PARAM("target_orientation_w", double,target_orientation_w);
    REGISTER_PARAM("target_position_x", double, target_position_x);
    REGISTER_PARAM("target_position_y", double, target_position_y);
    REGISTER_PARAM("target_position_z", double, target_position_z);
    //在LocateCenterPrimitive动作基元库解析函数中实例化需要用到的服务通信
    center_ask_client_ = std::make_shared<TemplateClientService<LocateObjectCenter>>(node_);
}

bool LocateCenterPrimitive::Excute() {
    center_ask_client_->Create("locate_center");//创立服务通讯客户端
    //检测服务端有无连接
    if(center_ask_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    vision_interfaces::srv::LocateObjectCenter::Request center_request;
    vision_interfaces::srv::LocateObjectCenter::Response center_response;
    //向服务端发送请求并获取服务端返回数据
    center_request.object_label=this->object_label;
    if(center_ask_client_->SendRequest(&center_request,&center_response)==false) {
        RCLCPP_ERROR(node_->get_logger(),"未连接至视觉服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(center_response.success == 0) {
        RCLCPP_ERROR(node_->get_logger(),"视觉识别失败！");
        return 0;
    }
    //对目标位姿进行赋值
    target_orientation_x = center_response.orientation.x;
    target_orientation_y = center_response.orientation.y;
    target_orientation_z = center_response.orientation.z;
    target_orientation_w = center_response.orientation.w;
    target_position_x = center_response.position.x;
    target_position_y = center_response.position.y;
    target_position_z = center_response.position.z;
    //打印出目标中心点坐标
    RCLCPP_INFO(node_->get_logger(),"物品%s中心坐标: x:%f,y:%f,z:%f",
                                    center_request.object_label.c_str(),
                                    center_response.position.x,
                                    center_response.position.y,
                                    center_response.position.z);
    
    return 1;

}

void LocateCenterPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("LocateCenterPrimitive"), "Stop function called.");
}


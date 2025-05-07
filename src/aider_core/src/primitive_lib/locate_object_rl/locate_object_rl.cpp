#include "aider_core/primitive_lib/locate_object_rl/locate_object_rl.hpp"

using vision_interfaces::srv::LocateObjectRL;
using namespace std::chrono_literals;


LocateRLPrimitive::LocateRLPrimitive() {
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：定位物体左右坐标点已激活！");//在LocateRLPrimitive动作基元库中传递大脑节点
    //初始化参数列表
    REGISTER_PARAM("object_label", std::string, object_label);
    REGISTER_PARAM("left_target_orientation_x", double, left_target_orientation_x);
    REGISTER_PARAM("left_target_orientation_y", double, left_target_orientation_y);
    REGISTER_PARAM("left_target_orientation_z", double, left_target_orientation_z);
    REGISTER_PARAM("left_target_orientation_w", double, left_target_orientation_w);
    REGISTER_PARAM("left_target_position_x", double, left_target_position_x);
    REGISTER_PARAM("left_target_position_y", double, left_target_position_y);
    REGISTER_PARAM("left_target_position_z", double, left_target_position_z);

    REGISTER_PARAM("right_target_orientation_x", double, right_target_orientation_x);
    REGISTER_PARAM("right_target_orientation_y", double, right_target_orientation_y);
    REGISTER_PARAM("right_target_orientation_z", double, right_target_orientation_z);
    REGISTER_PARAM("right_target_orientation_w", double, right_target_orientation_w);
    REGISTER_PARAM("right_target_position_x", double, right_target_position_x);
    REGISTER_PARAM("right_target_position_y", double, right_target_position_y);
    REGISTER_PARAM("right_target_position_z", double, right_target_position_z);

    //在LocateRLPrimitive动作基元库解析函数中实例化需要用到的服务通信
    rl_ask_client_ = std::make_shared<TemplateClientService<LocateObjectRL>>();
    rl_ask_client_->Create("locate_rl");//创立服务通讯客户端
}

bool LocateRLPrimitive::Excute() {
    //检测服务端有无连接
    if(rl_ask_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至视觉服务器，连接失败，程序退出！");
        return 0;
    }
    //设置服务通讯请求与应答应变量
    vision_interfaces::srv::LocateObjectRL::Request rl_request;
    vision_interfaces::srv::LocateObjectRL::Response rl_response;
    //向服务端发送请求并获取服务端返回数据
    rl_request.object_label=this->object_label;
    if(rl_ask_client_->SendRequest(&rl_request,&rl_response)==false) {
        RCLCPP_ERROR(aider_node->get_logger(),"未连接至视觉服务器，连接失败，程序退出！");
        return 0;
    } 
    //判断返回的数据是否识别成功
    if(rl_response.success == 0) {
        RCLCPP_ERROR(aider_node->get_logger(),"视觉识别失败！");
        return 0;
    }
    //对目标位姿进行赋值
    left_target_orientation_x = rl_response.leftorientation.x;
    left_target_orientation_y = rl_response.leftorientation.y;
    left_target_orientation_z = rl_response.leftorientation.z;
    left_target_orientation_w = rl_response.leftorientation.w;
    left_target_position_x = rl_response.leftposition.x;
    left_target_position_y = rl_response.leftposition.y;
    left_target_position_z = rl_response.leftposition.z;

    right_target_orientation_x = rl_response.rightorientation.x;
    right_target_orientation_y = rl_response.rightorientation.y;
    right_target_orientation_z = rl_response.rightorientation.z;
    right_target_orientation_w = rl_response.rightorientation.w;
    right_target_position_x = rl_response.rightposition.x;
    right_target_position_y = rl_response.rightposition.y;
    right_target_position_z = rl_response.rightposition.z;

    //打印出目标中心点坐标
    RCLCPP_INFO(aider_node->get_logger(),"物品%s左边坐标: x:%f,y:%f,z:%f右边坐标: x:%f,y:%f,z:%f",
                                    rl_request.object_label.c_str(),
                                    rl_response.leftposition.x,
                                    rl_response.leftposition.y,
                                    rl_response.leftposition.z,
                                    rl_response.rightposition.x,
                                    rl_response.rightposition.y,
                                    rl_response.rightposition.z);
    
    return 1;

}

void LocateRLPrimitive::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("LocateRLPrimitive"), "Stop function called.");
}


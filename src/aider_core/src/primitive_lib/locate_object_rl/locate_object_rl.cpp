#include "aider_core/primitive_lib/locate_object_rl/locate_object_rl.hpp"

using vision_interfaces::srv::LocateObjectRL;
using namespace std::chrono_literals;
//用到参数
//输入：object_name
//输出：left_target_orientation_x
//输出：left_target_orientation_y
//输出：left_target_orientation_z
//输出：left_target_orientation_w
//输出：left_target_position_x
//输出：left_target_position_y
//输出：left_target_position_z
//输出：right_target_orientation_x
//输出：right_target_orientation_y
//输出：right_target_orientation_z
//输出：right_target_orientation_w
//输出：right_target_position_x
//输出：right_target_position_y
//输出：right_target_position_z

LocateRLPrimitive::LocateRLPrimitive(std::string task_name,int task_instance_id) {
    aider_node = AiderNode::get_instance();
    param_center = ParamNode::get_instance("src/aider_core/config/parameters.yaml");
    this->task_name_ = task_name;
    this->task_instance_id_ = task_instance_id;
    //注册要用的参数
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "object_name");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_orientation_w");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "left_target_position_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_z");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_orientation_w");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_x");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_y");
    param_center->RegistParam(this->task_name_, this->task_instance_id_, "right_target_position_z");
    RCLCPP_INFO(aider_node->get_logger(), "动作基元：定位物体左右坐标点已激活！");//在LocateRLPrimitive动作基元库中传递大脑节点
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
    rl_request.object_label = std::any_cast<std::string>(param_center->GetParamValue(this->task_name_,this->task_instance_id_,"object_name").value());
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
    this->left_target_orientation_x = rl_response.leftorientation.x;
    this->left_target_orientation_y = rl_response.leftorientation.y;
    this->left_target_orientation_z = rl_response.leftorientation.z;
    this->left_target_orientation_w = rl_response.leftorientation.w;
    this->left_target_position_x = rl_response.leftposition.x;
    this->left_target_position_y = rl_response.leftposition.y;
    this->left_target_position_z = rl_response.leftposition.z;

    this->right_target_orientation_x = rl_response.rightorientation.x;
    this->right_target_orientation_y = rl_response.rightorientation.y;
    this->right_target_orientation_z = rl_response.rightorientation.z;
    this->right_target_orientation_w = rl_response.rightorientation.w;
    this->right_target_position_x = rl_response.rightposition.x;
    this->right_target_position_y = rl_response.rightposition.y;
    this->right_target_position_z = rl_response.rightposition.z;

    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_x", left_target_orientation_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_y", left_target_orientation_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_z", left_target_orientation_z);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_orientation_w", left_target_orientation_w);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_x", left_target_position_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_y", left_target_position_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "left_target_position_z", left_target_position_z);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_orientation_x", right_target_orientation_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_orientation_y", right_target_orientation_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_orientation_z", right_target_orientation_z);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_orientation_w", right_target_orientation_w);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_position_x", right_target_position_x);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_position_y", right_target_position_y);
    param_center->SetParamValue(this->task_name_, this->task_instance_id_, "right_target_position_z", right_target_position_z);

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


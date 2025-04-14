#include "aider_core/task_lib/grab_cup/grab_cup.hpp"


using vision_interfaces::srv::LocateObjectCenter;
using arm_interfaces::srv::SingleArmMove;
using namespace std::chrono_literals;

GrapCupTask::GrapCupTask(std::shared_ptr<rclcpp::Node> node)
    :node_(node){
    RCLCPP_INFO(node_->get_logger(), "主节点已共享！");//在grapcup动作库中传递大脑节点
    //在grapcup动作库解析函数中实例化需要用到的服务通信
    center_ask_client_ = std::make_shared<TemplateClientService<LocateObjectCenter>>(node_);
    single_arm_move_client_ = std::make_shared<TemplateClientService<SingleArmMove>>(node_);
}

void GrapCupTask::Excute() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "杯子抓取任务已开启！");
    center_ask_client_->Create("locate_center");//创立服务通讯客户端
    //检测服务端有无连接
    if(center_ask_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至服务器，连接失败，程序退出！");
        return;
    }
    //设置服务通讯请求与应答应变量
    vision_interfaces::srv::LocateObjectCenter::Request center_request;
    vision_interfaces::srv::LocateObjectCenter::Response center_response;
    //向服务端发送请求并获取服务端返回数据
    center_request.object_label="cup";
    if(center_ask_client_->SendRequest(&center_request,&center_response)==false) {
        RCLCPP_ERROR(node_->get_logger(),"未连接至视觉服务器，连接失败，程序退出！");
        return;
    } 
    //判断返回的数据是否识别成功
    if(center_response.success == 0) {
        RCLCPP_ERROR(node_->get_logger(),"视觉识别失败！");
        return;
    }
    //打印出目标中心点坐标
    RCLCPP_INFO(node_->get_logger(),"物品%s中心坐标: x:%f,y:%f,z:%f",
                                    center_request.object_label.c_str(),
                                    center_response.position.x,
                                    center_response.position.y,
                                    center_response.position.z);
    //对目标位姿进行赋值
    double target_orientation_x = center_response.orientation.x;
    double target_orientation_y = center_response.orientation.y;
    double target_orientation_z = center_response.orientation.z;
    double target_orientation_w = center_response.orientation.w;
    double target_psition_x = center_response.position.x;
    double target_psition_y = center_response.position.y;
    double target_psition_z = center_response.position.z;

    //创立手臂通讯服务端
    single_arm_move_client_->Create("single_arm_move_to");//创立服务通讯客户端
    //检测服务端有无连接
    if(single_arm_move_client_->Connect()==false) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"未连接至手臂服务器，连接失败，程序退出！");
        return;
    }
    //设置服务通讯请求与应答应变量
    arm_interfaces::srv::SingleArmMove::Request single_arm_move_request;
    arm_interfaces::srv::SingleArmMove::Response arm_move_response;
    //向服务端发送请求并获取服务端返回数据
    single_arm_move_request.which_arm="left_arm";
    single_arm_move_request.orientation.x=target_orientation_x;
    single_arm_move_request.orientation.y=target_orientation_y;
    single_arm_move_request.orientation.z=target_orientation_z;
    single_arm_move_request.orientation.w=target_orientation_w;
    single_arm_move_request.position.x=target_psition_x;
    single_arm_move_request.position.y=target_psition_y;
    single_arm_move_request.position.z=target_psition_z;
    if(single_arm_move_client_->SendRequest(&single_arm_move_request,&arm_move_response)==false) {
        RCLCPP_ERROR(node_->get_logger(),"未连接至手臂服务器，连接失败，程序退出！");
        return;
    }
    //判断点位是否到达成功
    if(arm_move_response.success == 0) {
        RCLCPP_ERROR(node_->get_logger(),"移动失败！");
        return;
    }

    RCLCPP_INFO(node_->get_logger(),"抓取成功！");

    

}

void GrapCupTask::Stop() {
    RCLCPP_INFO(rclcpp::get_logger("GrabCupTask"), "Stop function called.");
}






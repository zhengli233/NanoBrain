#ifndef LOCATE_OBJECT_CENTER_HPP_
#define LOCATE_OBJECT_CENTER_HPP_
#include "../primitive_lib.hpp"
#include "aider_global_node.hpp"
#include "vision_interfaces/srv/locate_object_center.hpp"
#include "Template_Client_Service.hpp"
#include "Client.hpp"

using vision_interfaces::srv::LocateObjectCenter;


class LocateCenterPrimitive : public Primitive {
    public:
        explicit LocateCenterPrimitive();
        virtual bool Excute();
        virtual void Stop();

    private:
        std::shared_ptr<Client> center_ask_client_;//设置服务通信客户端
        //以下是本动作基元所需变量
        std::string object_label;
        double target_orientation_x;
        double target_orientation_y;
        double target_orientation_z;
        double target_orientation_w;
        double target_position_x;
        double target_position_y;
        double target_position_z;
    };







#endif  // LOCATE_OBJECT_CENTER_HPP_

#include "rclcom.h"
#include<QDebug>
#include<sstream>

rclcom::rclcom(){
    rclcpp::init(0,NULL); //初始化ros
    node=rclcpp::Node::make_shared("node"); //实例化ros2节点
//    sub_simpleMap=node->create_subscription<nav_msgs::msg::OccupancyGrid>
//            ("/map",rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local(),std::bind(&rclcom::callback_revSimpleMap,this,std::placeholders::_1)); //创建消息订阅者并绑定回调函数
//    sub_path=node->create_subscription<nav_msgs::msg::Path>
//            ("/plan",10,std::bind(&rclcom::callback_revPath,this,std::placeholders::_1));
//    //初始化tf2
//    tfBuffer=std::make_unique<tf2_ros::Buffer>(node->get_clock());
//    tfListener=std::make_shared<tf2_ros::TransformListener>(*tfBuffer);
    sub_can=node->create_subscription<sensor_driver_msgs::msg::ChassisCanRecived> //初始化can消息订阅者
            ("/can",10,std::bind(&rclcom::callback_revCan,this,std::placeholders::_1));
    
}

void rclcom::run(){
    while(rclcpp::ok()){
        rclcpp::spin_some(node); //spin节点
    }
    rclcpp::shutdown();
}

void rclcom::addCamera(QString cameraName, QString topicName){
    auto sub_tempCamera=node->create_subscription<sensor_msgs::msg::Image>
            (topicName.toStdString(),10,std::bind(&rclcom::callback_revImage,this,std::placeholders::_1));
    subs_camera.insert(cameraName,sub_tempCamera);
}

void rclcom::callback_revImage(const sensor_msgs::msg::Image::SharedPtr msgs){
//    qDebug()<<"收到摄像头信息";
//    qDebug()<<QString::fromStdString(msgs->header.frame_id);
    emit signal_revImage(msgs);
}

void rclcom::callback_revCan(const sensor_driver_msgs::msg::ChassisCanRecived::SharedPtr msgs){
    qDebug()<<"收到车辆底盘can消息！";
    //TODO:整理成前端可以接受的格式

    
}

//void rclcom::callback_revSimpleMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msgs){
//    qDebug()<<"收到棚格地图消息！";
//    //for(int i=0;i<msgs->data.size();i++) qDebug()<<msgs->data[i];
//    QImage map=Utilities::simpleMap_to_QImage(msgs);
//    resolution=msgs->info.resolution;
//    double origin_x=msgs->info.origin.position.x;
//    double origin_y=msgs->info.origin.position.y;
//    worldOrigin.setX(fabs(origin_x/resolution)); //利用地图信息计算出一些值，方便后面使用
//    worldOrigin.setY(fabs((origin_y+map.height()*resolution)/resolution));
//    emit signal_revSimpleMap(map); //发送收到地图信号，并代入地图数据
//}

//void rclcom::callback_revPath(const nav_msgs::msg::Path::SharedPtr msgs){
//    qDebug()<<"收到路径信息！";
//    QVector<QPointF>pathPoints(msgs->poses.size());
//    for(int i=0;i<msgs->poses.size();i++){
//        pathPoints[i]=Utilities::worldPoint_to_scenePoint(QPointF(msgs->poses.at(i).pose.position.x,msgs->poses.at(i).pose.position.y),worldOrigin,resolution); //坐标系转换
//    }
//    emit signal_revPath(pathPoints);
//}

//void rclcom::getPose(){
//    try{
//        geometry_msgs::msg::TransformStamped transform
//                =tfBuffer->lookupTransform("map","base_link",tf2::TimePointZero);
//        geometry_msgs::msg::Quaternion msgs_quat=transform.transform.rotation;
//        tf2::Quaternion q;
//        tf2::fromMsg(msgs_quat,q); //获取时延数
//        tf2::Matrix3x3 matrix(q); //将时延数转换为matrix类型
//        double roll,pitch,yaw;
//        matrix.getRPY(roll,pitch,yaw); //获取到位置
//        location.roll=roll;
//        location.pitch=pitch;
//        location.yaw=yaw;
//        QPointF scenePoint= //进行坐标系转换（世界-->图元）
//                Utilities::worldPoint_to_scenePoint(QPointF(transform.transform.translation.x,transform.transform.translation.y),worldOrigin,resolution);
//        location.x=scenePoint.x();
//        location.y=scenePoint.y();
////        qDebug()<<"位置："<<location.x<<" "<<location.y;
////        qDebug()<<"角度："<<yaw;
//        emit signal_revLocation(location); //发送位置信息信号      
//    }
//    catch(tf2::TransformException& ex){
//        //qDebug()<<"tf转换异常"<<":"<<ex.what();
//    }
//}

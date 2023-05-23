#ifndef RCLCOM_H
#define RCLCOM_H

#include <QObject>
#include<iostream>
#include<QThread>
#include<rclcpp/rclcpp.hpp>
#include"Location_t.h"
#include"tf2_ros/transform_listener.h"
#include"tf2/LinearMath/Quaternion.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
#include"nav_msgs/msg/occupancy_grid.hpp"
#include"nav_msgs/msg/path.hpp"
#include"Utilities.h"
#include"QPointF"
#include<QVector>
#include<QMap>
#include"sensor_msgs/msg/image.hpp"
#include"sensor_driver_msgs/msg/chassis_can_recived.hpp"

class rclcom:public QThread
{
    Q_OBJECT
public:
    rclcom();
    void run() override;
    void addCamera(QString cameraName,QString topicName); //添加摄像机的实际通讯订阅者

private:
    std::shared_ptr<rclcpp::Node>node; //节点指针
//    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_simpleMap; //地图消息订阅者指针
//    rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr sub_path; //导航路径消息订阅者指针
//    std::unique_ptr<tf2_ros::Buffer>tfBuffer; //tf变换相关指针
//    std::shared_ptr<tf2_ros::TransformListener>tfListener;
    QMap<QString,rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr> subs_camera; //摄像机订阅者指针
    rclcpp::Subscription<sensor_driver_msgs::msg::ChassisCanRecived>::SharedPtr sub_can; //车辆底盘can信息订阅
//    Location_t location; //位置变量对象
//    QPointF worldOrigin; //世界坐标系原点在图元坐标系下的位置
//    double resolution; //地图分辨率
    //rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_tempCamera;

private:
//    void callback_revSimpleMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msgs); //订阅者回调函数
//    void callback_revPath(const nav_msgs::msg::Path::SharedPtr msgs); //导航路径消息订阅者回调函数
    void callback_revImage(const sensor_msgs::msg::Image::SharedPtr msgs); //接受到摄像头图像信息回调函数
    void callback_revCan(const sensor_driver_msgs::msg::ChassisCanRecived::SharedPtr msgs);
    //void getPose();

signals:
//    void signal_revSimpleMap(QImage map); //收到栅格地图数据信号
//    void signal_revLocation(Location_t location); //收到位置信息的信号
//    void signal_revPath(QVector<QPointF> pathPoints); //收到导航路径点解信号
    void signal_revImage(sensor_msgs::msg::Image::SharedPtr msg); //收到摄像头的信号
    //void signal_changeGear(QString gear); //换档信号
    //void signal_changeTurningLight(int type); //转向灯信号
};

#endif // RCLCOM_H

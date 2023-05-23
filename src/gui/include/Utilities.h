#ifndef UTILITIES_H
#define UTILITIES_H

#include<QVector>
#include<QImage>
#include"nav_msgs/msg/occupancy_grid.hpp"
#include"sensor_msgs/msg/image.hpp"
#include<QPointF>
#include<QPixmap>
//#include<cv_bridge/cv_bridge.h>

class Utilities
{
public:
    Utilities();
    static QImage simpleMap_to_QImage(nav_msgs::msg::OccupancyGrid::SharedPtr msgs); //将地图消息转换为QImage对象,并且直接将地图坐标系转换为图元坐标系
    //static QPixmap rosImage_to_QPixmap(sensor_msgs::msg::Image::SharedPtr msgs); //将ros格式的Image消息转换为QImage对象
    static QPointF worldPoint_to_scenePoint(QPointF point,QPointF worldOrigin,double mapResolution); //将世界坐标系下的一个点转化为图元坐标系下的一个点
    static QPointF scenePoint_to_worldPoint(QPointF point,QPointF worldOrigin,double mapResolution); //将图元坐标系下的一个点转换到世界坐标系下
};

#endif // UTILITIES_H

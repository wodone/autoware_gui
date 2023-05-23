#include "Utilities.h"
#include<QDebug>

Utilities::Utilities(){}

QImage Utilities::simpleMap_to_QImage(nav_msgs::msg::OccupancyGrid::SharedPtr msgs){
    QImage map(msgs->info.width,msgs->info.height,QImage::Format_RGB32);
    //qDebug()<<msgs->info.width<<msgs->info.height;
    for(int i=0;i<msgs->data.size();i++){
        int x=i%(msgs->info.width);
        int y=i/(msgs->info.width);
        y=msgs->info.height-y-1; //转化坐标系
        QColor color;
        if(msgs->data[i]==0) color=Qt::white;
        else if(msgs->data[i]==100) color=Qt::black;
        else color=Qt::gray;
        map.setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    }
    //map.save("/home/ros2/test_map_rev/simpleMap.png"); //保存到测试路径，调试使用
    return map;
}

//QPixmap Utilities::rosImage_to_QPixmap(sensor_msgs::msg::Image::SharedPtr msgs){
//    auto cv_ptr=cv_bridge::toCvCopy(msgs,sensor_msgs::image_encodings::RGB8);
//    auto imageDate=cv_ptr->image.data;
//    return QPixmap::fromImage(QImage(imageDate,msgs->width,msgs->height,msgs->step,QImage::Format_RGB888));
//}

QPointF Utilities::worldPoint_to_scenePoint(QPointF pointInWorld,QPointF worldOriginInScene, double mapResolution){
    QPointF pointInScene;
    pointInScene.setX(worldOriginInScene.x()+pointInWorld.x()/mapResolution);
    pointInScene.setY(worldOriginInScene.y()-pointInWorld.y()/mapResolution);
    return pointInScene;
}

QPointF Utilities::scenePoint_to_worldPoint(QPointF pointInScene,QPointF sceneOriginInWorld, double mapResolution){
    QPointF pointInWorld;
    pointInWorld.setX(sceneOriginInWorld.x()+pointInScene.x()*mapResolution);
    pointInWorld.setY(sceneOriginInWorld.y()-pointInScene.y()*mapResolution);
    return pointInWorld;
}


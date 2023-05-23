#ifndef MAPITEM_H
#define MAPITEM_H
#define PI 3.1415926

#include <QObject>
#include<QGraphicsItem>
#include<QGraphicsSceneWheelEvent>
#include"Location_t.h"

class mapItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    mapItem();
    ~mapItem();
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget=nullptr) override;
    QRectF boundingRect()const override;
    void wheelEvent(QGraphicsSceneWheelEvent* event) override; //鼠标滚轮事件，对地图放大和缩小
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public slots:
    void updateMap(QImage); //更新地图
    void updateLocation(Location_t); //更新位置信息
    void updatePath(QVector<QPointF>); //更新导航路径

private:
    void drawMap(QPainter* painter);
    void drawLocation(QPainter* painter);
    void drawPath(QPainter* painter);
    void drawPoint(QPainter* painter);

private:
    QPixmap* pix_car;
    QPixmap* pix_navigationPoint;
    QImage map; //地图信息
    QVector<QPointF> path; //导航路径信息
    QPointF navigationPoint; //导航点信息
    Location_t location; //机器人位置信息
    double scaleValue=1.0; //缩放比例
    QPointF pressedPoint; //鼠标按下的位置
    bool isPressed=false; //鼠标是否被按下
    bool noMap=true; //没有地图信息
    bool noLocation=true; //没有位置信息
    bool noPoint=true;  //没有导航点信息
};

#endif // MAPITEM_H

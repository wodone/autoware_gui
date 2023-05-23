#include "mapItem.h"
#include<QPainter>
#include<QDebug>
#include<QWidget>

mapItem::mapItem(){
    pix_car=new QPixmap(":/Image/Icon/Image/car.png"); //加载图片
    pix_navigationPoint=new QPixmap(":/Image/Icon/Image/point.png");
    QMatrix mx; //定义旋转矩阵，将车辆图片顺时针旋转90度
    mx.rotate(90);
    *pix_car=pix_car->transformed(mx,Qt::SmoothTransformation); //平滑转换
}

mapItem::~mapItem(){
    delete pix_car; //释放图片
    delete pix_navigationPoint;
}

void mapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(!noMap) drawMap(painter);
    if(!noLocation) drawLocation(painter);
    drawPath(painter);
    if(!noPoint) drawPoint(painter);
}

void mapItem::drawMap(QPainter *painter){
    painter->drawImage(0,0,map);
}

void mapItem::drawLocation(QPainter *painter){
    painter->save();
    painter->translate(location.x,location.y);
    painter->rotate(-location.yaw*180/PI);
    painter->drawPixmap(-pix_car->width()/2,-pix_car->height()/2,*pix_car); //绘制位置
    painter->restore();
}

void mapItem::drawPath(QPainter *painter){
    QPen pen; //设置导航路径绘制参数
    pen.setWidth(1);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    for(int i=0;i<path.size();i++) painter->drawPoint(path[i]); //绘制导航路径
}

void mapItem::drawPoint(QPainter *painter){
    painter->save();
    painter->translate(navigationPoint.x(),navigationPoint.y());
    painter->drawPixmap(-pix_navigationPoint->width()/2,-pix_navigationPoint->height()/2,*pix_navigationPoint); //导航点
    painter->restore();
}

void mapItem::updatePath(QVector<QPointF> pathPoints){
    qDebug()<<"导航路径更新！";
    this->path=pathPoints;
    update();
}

void mapItem::updateMap(QImage map){ //更新地图
    qDebug()<<"地图更新！";
    this->map=map;
    noMap=false;
    update();
}

void mapItem::updateLocation(Location_t location){
    //qDebug()<<"位置更新！";
    this->location=location;
    noLocation=false;
    update();
}

void mapItem::wheelEvent(QGraphicsSceneWheelEvent *event){
    double old_scaleValue=scaleValue;
    if(event->delta()>0) scaleValue=scaleValue*1.1;
    else scaleValue=scaleValue*0.9;
    setScale(scaleValue);
    if(event->delta()>0) moveBy(-event->pos().x()*old_scaleValue*0.1,-event->pos().y()*old_scaleValue*0.1);
    else moveBy(event->pos().x()*old_scaleValue*0.1,event->pos().y()*old_scaleValue*0.1);
}

void mapItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        isPressed=true;
        pressedPoint=event->pos();
    }
    else navigationPoint=event->pos();
}

void mapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if(isPressed){
        QPointF point=(event->pos()-pressedPoint)*scaleValue;
        moveBy(point.x(),point.y());
    }
}

void mapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        pressedPoint=QPointF();
        isPressed=false;
    }
    else{
        noPoint=false;
        update();
    }
}

QRectF mapItem::boundingRect()const{
    return QRectF(0,0,map.width(),map.height());
}

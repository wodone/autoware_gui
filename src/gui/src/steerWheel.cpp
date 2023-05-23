#include "steerWheel.h"

steerWheel::steerWheel(QWidget* parent):QWidget(parent){}

void steerWheel::paintEvent(QPaintEvent *event){
    int width=this->width();
    int height=this->height();
    auto painter=new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing); //启动抗锯齿
    painter->translate(width/2, height/2);
    int side = qMin(width, height);
    painter->scale(side / 200.0, side / 200.0);      /* 比例缩放 */
    int out_circle_radius = 58*1.7;
    int in_circle_radius = 50*1.7;
    QPointF points[] = {
            QPointF(50,-8),
            QPointF(30,-8),
            QPointF(25,-15),
            QPointF(-25,-15),
            QPointF(-30,-8),
            QPointF(-50,-8),
            QPointF(-50,5),
            QPointF(-30,5),
            QPointF(-8,25),
            QPointF(-8,50),
            QPointF(8,50),
            QPointF(8,25),
            QPointF(30,5),
            QPointF(50,5)
    };
    for(int i=0;i<14;i++) points[i]=points[i]*1.73;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->rotate(0);
    painter->setBrush(Qt::black);
    painter->drawEllipse(-out_circle_radius, -out_circle_radius, out_circle_radius * 2, out_circle_radius * 2);
    painter->setBrush(QColor(238, 238, 236));
    painter->drawEllipse(-in_circle_radius, -in_circle_radius, in_circle_radius * 2, in_circle_radius * 2);
    painter->setBrush(Qt::black);
    painter->drawPolygon(points, sizeof(points)/sizeof(points[0]));
    painter->restore();
    delete painter;
}

#ifndef MYCAR_H
#define MYCAR_H

#include <QWidget>
#include<QPainter>
#include<memory>
#include"radarLocation.h"
#include<QMap>
#include<QMessageBox>

class Mycar : public QWidget
{
    Q_OBJECT
public:
    explicit Mycar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;

private:
    double ratio=2.2;
    double width=60;
    double height=150;
    double gap=15;
    QPointF leftTop{120,40};
    QPainter painter{this};
    QColor color_car{Qt::gray}; //车身颜色
    QColor color_radar{Qt::black}; //超声波雷达点颜色
    QPointF points[8]; //主框架点位
    QPointF points_radar[20]; //超声波雷达点位
    QMap<int,int>radarTypeMap; //超声波雷达状态表
    QMap<int,std::shared_ptr<radarLocation>>radarLocationMap; //超声波雷达雷达线位置表
    bool isDrawMain=false;

public slots:
    void updateRadarTypeMap(QMap<int,int>&radarTypeMap); //更新雷达状态表

private:
    void drawMain();
    void drawRadar(std::shared_ptr<radarLocation> rectangle,int type,int direction); //再雷达点绘制超声波线,type表示红色超声波线的个数
    void drawAllRadar(); //画出超声波雷达信息
    void getLocationMap(); //得到位置表

signals:

};

#endif // MYCAR_H

#ifndef STEERWHEEL_H
#define STEERWHEEL_H

#include <QObject>
#include <QWidget>
#include<QPainter>

class steerWheel:public QWidget
{
public:
    steerWheel(QWidget* parent);
    void paintEvent(QPaintEvent* event) override;

private:
    //QPainter* painter;
    //double
};

#endif // STEERWHEEL_H

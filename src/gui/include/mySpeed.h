#ifndef MYSPEED_H
#define MYSPEED_H

#include <QWidget>


class MySpeed : public QWidget
{
    Q_OBJECT

public:
    MySpeed(QWidget *parent = nullptr);
    ~MySpeed();

    void paintEvent(QPaintEvent *event);
    //void timerEvent(QTimerEvent *e);

private:
    void drawFrame(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);

    void drawPointer(QPainter *painter);
    void drawSpeed(QPainter *painter);

    void drawUnit(QPainter *painter);


    int speed;
    int time_id;
    int status;
    qreal m_angle;
    QColor m_foreground;

    int m_maxValue;
    int m_minValue;
    int m_startAngle;
    int m_endAngle;

    int m_scaleMajor;
    int m_scaleMinor;
    double m_value;
    int m_precision;
    //QTimer *m_updateTimer;
    QString m_units;
    QString m_title;

};
#endif // MYSPEED_H

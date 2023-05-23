
#include "mySpeed.h"

#include <QPainter>
#include <QBrush>
#include <QLabel>
#include <QTimerEvent>
#include <QLinearGradient>
#include <QFont>
#include <QtMath>

MySpeed::MySpeed(QWidget *parent)
    : QWidget(parent)
{
    //resize(800, 480);
    //setWindowTitle("test");

    m_foreground = Qt::black;

    speed = 0;
    status = 0;

    m_startAngle = 45;
    m_endAngle = 45;

    m_minValue = 0;
    m_maxValue = 40;

    m_scaleMajor = 4;//分度
    m_scaleMinor = 10;
    m_units = "km/h";
    m_title = "My Speed";
    m_precision = 0;
    m_value = 0;

    m_angle = (qreal)270/(m_maxValue-1);

    //time_id = this->startTimer(50);
}

MySpeed::~MySpeed()
{
}

void MySpeed::paintEvent(QPaintEvent *event)
{
    int width=this->width();
    int height=this->height();


    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing); //启动抗锯齿

    painter.translate(width/2, height/2);

    int side = qMin(width, height);
    painter.scale(side / 200.0, side / 200.0);      /* 比例缩放 */

    drawFrame(&painter);

    drawScale(&painter);                                 /* 画刻度线 */

    drawScaleNum(&painter);                          /* 画刻度数值值 */
    drawUnit(&painter);
    drawPointer(&painter);

    drawSpeed(&painter);
}

void MySpeed::drawFrame(QPainter *painter)
{
    painter->save();
    // 半径100
    int radius = 97;

    painter->setBrush(QBrush(QColor(0, 255, 0, 255), Qt::SolidPattern));
    painter->drawArc(-radius, -radius, radius<<1, radius<<1, -135*16, -270*16);

    painter->restore();

}

// 绘制刻度线
void MySpeed::drawScale(QPainter *painter)
{

    painter->save();
    painter->rotate(m_startAngle);
    int steps = (m_scaleMajor * m_scaleMinor); //相乘后的值是分的份数
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps; //每一个份数的角度

    // painter->setPen(m_foreground); //m_foreground是颜色的设置
    // QPen pen = painter->pen(); //第一种方法
    QPen pen ;
    pen.setColor(m_foreground); //推荐使用第二种方式
    for (int i = 0; i <= steps; i++)
    {
        if (i % m_scaleMinor == 0)//整数刻度显示加粗
        {
            pen.setWidth(1); //设置线宽
            painter->setPen(pen); //使用面向对象的思想，把画笔关联上画家。通过画家画出来

            painter->drawLine(0, 90*0.97, 0, 97); //两个参数应该是两个坐标值
        }
        else
        {
           pen.setWidth(0);
           painter->setPen(pen);
           painter->drawLine(0, 95*0.97, 0, 97);
        }
       painter->rotate(angleStep);
    }
    painter->restore();
}
// 绘制刻度
void MySpeed::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(m_foreground);
    //m_startAngle是起始角度，m_endAngle是结束角度，m_scaleMajor在一个量程中分成的刻度数
    double startRad = ( 270-m_startAngle) * (3.14 / 180);
    double deltaRad = (360 - m_startAngle - m_endAngle) * (3.14 / 180) / m_scaleMajor;
    double sina,cosa;
    int x, y;
    QFontMetricsF fm(this->font());
    double w, h, tmpVal;
    QString str;

    for (int i = 0; i <= m_scaleMajor; i++)
    {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);

       tmpVal = 1.0 * i *((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;
       // tmpVal = 50;
        str = QString( "%1" ).arg(tmpVal);  //%1作为占位符   arg()函数比起 sprintf()来是类型安全的
        w = fm.size(Qt::TextSingleLine,str).width();
        h = fm.size(Qt::TextSingleLine,str).height();
        x = 82 * cosa - w / 2;
        y = -82 * sina + h / 4;
        painter->drawText(x, y, str); //函数的前两个参数是显示的坐标位置，后一个是显示的内容，是字符类型""

    }
    painter->restore();
}

void MySpeed::drawPointer(QPainter *painter)
{
    int radius = 100;
    QPoint point[4] = {
        QPoint(0, 10),
        QPoint(-10, 0),
        QPoint(0, -80),
        QPoint(10, 0),
    };

    painter->save();

    QLinearGradient linear;
    linear.setStart(-radius, -radius);
    linear.setFinalStop(radius<<1, radius<<1);
    linear.setColorAt(0, QColor(0, 255, 255, 0));
    linear.setColorAt(1, QColor(0, 255, 255, 255));
    painter->setPen(Qt::NoPen);
    painter->setBrush(linear);
    painter->drawPie(-radius, -radius, radius<<1, radius<<1, 225 * 16, -(m_angle * this->speed) * 16);

    painter->restore();

    painter->save();

    painter->setBrush(QBrush(QColor(0, 0, 0, 255), Qt::SolidPattern));
    painter->rotate(-135 + this->speed * m_angle);
    painter->drawPolygon(point, 4);

    painter->restore();
}

void MySpeed::drawSpeed(QPainter *painter)
{
    painter->save();

    painter->setPen(QColor("#0"));
    //  绘制速度
    QFont font("Times", 10, QFont::Bold);
    font.setBold(true);
    font.setPixelSize(46);
    painter->setFont(font);
    painter->drawText(-60, 0, 120, 92, Qt::AlignCenter, QString::number(speed));
    painter->restore();
}

void MySpeed::drawUnit(QPainter *painter)
{
    QString str = QString("%1").arg(m_units);
    QFontMetricsF fm(font());
    double w = fm.size(Qt::TextSingleLine,str).width();
    painter->setPen(m_foreground);
    painter->drawText(-w / 2, 82, str);
}

//void MySpeed::timerEvent(QTimerEvent *e)
//{
//    int timerId = e->timerId();

//    if(this->time_id == timerId) {
//        if(this->status == 0) {
//            this->speed += 1;
//            if(this->speed >= m_maxValue)
//                this->status = 1;
//        }else {
//            this->speed -= 1;
//            if(this->speed <= 0)
//                this->status = 0;

//        }

//        this->update();
//    }
//}

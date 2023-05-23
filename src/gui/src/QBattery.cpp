#include "QBattery.h"
#include <QTimer>
#include <QPainter>
#include <QPen>
#include<QDebug>


QBattery::QBattery(QWidget *parent)
{
    mBorderColor = QColor(100, 100, 100);
    mNormalColorStart = QColor(50, 205, 51);        //电池正常电量时的渐变开始颜色
    mNormalColorEnd = QColor(60, 179, 133);          //电池正常电量时的渐变结束颜色
    mWarningColorStart = QColor(250, 118, 113);
    mWarningColorEnd = QColor(204, 38, 38);


    mBorderRadius = 1;
    mBorderWidth = 2;
    mBatteryHeadWidth = 6;
    mBatteryHeadHeight = 20;
    mBatteryWidth = 80;
    mBatteryHeight = 40;
    mElectricBorder = 2;
    mWarningValue = 20.0;
    mCurrentValue = 60.0;

    mAnimationMsecs = 500; //动画运行时间，单位微妙

    barreryValueAnimation = new QPropertyAnimation(this,"value");
}

QBattery::~QBattery()
{
    delete barreryValueAnimation;
}

void QBattery::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing); //设置抗锯齿

    int batteryWidth = mBatteryWidth + mBatteryHeadWidth + 3*mBorderWidth; //计算电池总体的长和宽
    int batteryHeight = mBatteryHeight +2*mBorderWidth;
    float ratioX = (float)width()/batteryWidth;         //计算电池与实际窗口的长宽比
    float ratioY = (float)height()/batteryHeight;
    int windowWidth;
    int windowHeight;

    //根据窗口缩放，计算实际缩放后的窗口大小
    if(ratioX > ratioY){
        windowWidth = batteryWidth*ratioY;
        windowHeight = height();
    }else{
        windowWidth = width();
        windowHeight = batteryHeight*ratioX;
    }

    //计算窗口缩放后的电池的长宽等数据
    float ratio = qMin(ratioX,ratioY);
    int ratioWidth = mBatteryWidth*ratio;
    int ratioHeight = mBatteryHeight*ratio;
    int ratioBorderWidth = mBorderWidth*ratio;
    int ratioBatteryHeadWidth = mBatteryHeadWidth*ratio;
    int ratioBatteruHeadHeight = mBatteryHeadHeight*ratio;
    int ratioElectricBorder = mElectricBorder*ratio;

    painter.setViewport(0,0,windowWidth,windowHeight);  //设置视图窗口
    painter.setWindow(-windowWidth/2,-windowHeight/2,windowWidth,windowHeight);//设置窗口坐标原点为视口区域
                                                                               //的中心，只有视图坐标尺寸和窗口坐标尺寸比例相同时，才不会导致图形拉伸变形


    //绘制电池轮廓
    QPen pen;
    pen.setWidth(ratioBorderWidth);
    pen.setColor(mBorderColor);
    painter.setPen(pen);
    painter.drawRect(-ratioWidth/2,-ratioHeight/2,ratioWidth,ratioHeight);

    //绘制电池正极
    QBrush brush;
    brush.setColor(mBorderColor);
    brush.setStyle(Qt::SolidPattern); //画刷填充样式
    painter.setBrush(brush);
    painter.drawRect(ratioWidth/2,-ratioBatteruHeadHeight/2,ratioBatteryHeadWidth,ratioBatteruHeadHeight);

    //填充电池颜色
    painter.setPen(Qt::NoPen);
    QLinearGradient linearGradient(-ratioWidth/2+ratioElectricBorder,-ratioHeight/2+ratioElectricBorder,
                                   -ratioWidth/2+ratioElectricBorder,
                                   -ratioHeight/2+ratioElectricBorder+ratioHeight-2*ratioElectricBorder);
//    brush.setStyle(Qt::CrossPattern); //画刷填充样式

    if(mCurrentValue > mWarningValue){
        linearGradient.setColorAt(0,mNormalColorStart);
        linearGradient.setColorAt(1,mNormalColorEnd);
        brush.setStyle(Qt::LinearGradientPattern);
        painter.setBrush(linearGradient);
        painter.drawRect(-ratioWidth/2+ratioElectricBorder,-ratioHeight/2+ratioElectricBorder,
                         mCurrentValue/100*(ratioWidth-2*ratioElectricBorder),ratioHeight-2*ratioElectricBorder);
    }else{
        linearGradient.setColorAt(0,mWarningColorStart);
        linearGradient.setColorAt(1,mWarningColorEnd);
        painter.setBrush(linearGradient);
        painter.drawRect(-ratioWidth/2+ratioElectricBorder,-ratioHeight/2+ratioElectricBorder,
                         mCurrentValue/100*(ratioWidth-2*ratioElectricBorder),ratioHeight-2*ratioElectricBorder);
    }

    //绘制电池电量文字
    QFont font = this->font();
    //qDebug()<<"font.pixelSize = "<<font.pixelSize();
    font.setPixelSize(10*ratio);
    this->setFont(font);
    QFontMetrics textSize = QWidget::fontMetrics();
    //qDebug()<<"textSize.height() = "<<textSize.height()<<"textSize.maxWidth()"<<textSize.maxWidth();
    QString powStr=QString::asprintf("%.2f%%",mCurrentValue);
    QRect textRect=textSize.tightBoundingRect(powStr);//得到字符串的rect

    pen.setColor("black"); //划线颜色
    painter.setPen(pen);
    painter.drawText(0-textRect.width()/2,textRect.height()/2,powStr);
}


double QBattery::value() const
{
    return mCurrentValue;
}


void QBattery::setValue(const double value)
{
    mCurrentValue = value;
    this->repaint();
}

double QBattery::minValue() const
{
    return mMinValue;
}

void QBattery::setMinValue(double minValue)
{
    mMinValue = minValue;
}

double QBattery::maxValue() const
{
    return mMaxValue;
}

void QBattery::setMaxValue(double maxValue)
{
    mMaxValue = maxValue;
}


void QBattery::setElecValue(int value)
{
    barreryValueAnimation->setDuration(mAnimationMsecs);
    barreryValueAnimation->setStartValue(mCurrentValue);
    barreryValueAnimation->setEndValue((double)value);
    barreryValueAnimation->start();
}

void QBattery::setElecValue(double value)
{
    barreryValueAnimation->setDuration(mAnimationMsecs);
    barreryValueAnimation->setStartValue(mCurrentValue);
    barreryValueAnimation->setEndValue(value);
    barreryValueAnimation->start();
}

double QBattery::warningValue() const
{
    return mWarningValue;
}


void QBattery::setWarningValue(double warningValue)
{
    mWarningValue = warningValue;
    this->repaint();
}

void QBattery::setWarningValue(int warningValue)
{
    mWarningValue = (double)warningValue;
    this->repaint();
}

QColor QBattery::borderColor() const
{
    return mBorderColor;
}

void QBattery::setBorderColor(const QColor &borderColor)
{
    mBorderColor = borderColor;
    this->repaint();
}

QColor QBattery::warningColorStart() const
{
    return mWarningColorStart;
}

void QBattery::setWarningColorStart(const QColor &warningColorStart)
{
    mWarningColorStart = warningColorStart;
    this->repaint();
}

QColor QBattery::warningColorEnd() const
{
    return mWarningColorEnd;
}

void QBattery::setWarningColorEnd(const QColor &warningColorEnd)
{
    mWarningColorEnd = warningColorEnd;
    this->repaint();
}

QColor QBattery::normalColorStart() const
{
    return mNormalColorStart;
}

void QBattery::setNormalColorStart(const QColor &normalColorStart)
{
    mNormalColorStart = normalColorStart;
    this->repaint();
}

QColor QBattery::normalColorEnd() const
{
    return mNormalColorEnd;
}

void QBattery::setNormalColorEnd(const QColor &normalColorEnd)
{
    mNormalColorEnd = normalColorEnd;
    this->repaint();
}

int QBattery::animationMsecs() const
{
    return mAnimationMsecs;
}

void QBattery::setAnimationMsecs(const int animationMsecs)
{
    mAnimationMsecs = animationMsecs;
    this->repaint();
}

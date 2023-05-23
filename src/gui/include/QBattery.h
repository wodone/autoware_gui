#ifndef QBATTERY_H
#define QBATTERY_H

#include <QWidget>
#include <QPropertyAnimation>

/**
 *  1. 可以设置电池电池尺寸，并且电池尺寸可以跟随控件大小比例切换
 *  2. 可以设置电池电量，电池电量以动画的形式变化。
 *  3. 可以设置电量变化动画时间。
 *  2. 可设置电池电量警戒值。
 *  3. 可设置电池电量正常颜色和报警颜色。
 *  4. 可设置边框颜色。
 * 问题：
 *  1. 当直接调用设置电量属性接口，不能实现动画效果
 *  2. 还没有显示充电状态
 */


class QBattery : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(double warningValue READ warningValue WRITE setWarningValue)
    Q_PROPERTY(QColor warningColorStart READ warningColorStart WRITE setWarningColorStart)
    Q_PROPERTY(QColor warningColorEnd READ warningColorEnd WRITE setWarningColorEnd)
    Q_PROPERTY(QColor normalColorStart READ normalColorStart WRITE setNormalColorStart)
    Q_PROPERTY(QColor normalColorEnd READ normalColorEnd WRITE setNormalColorEnd)
    Q_PROPERTY(int animatonMsecs READ animationMsecs WRITE setAnimationMsecs);

//    Q_PROPERTY(double step READ getStep WRITE setStep)
//    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth)
//    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
//    Q_PROPERTY(int bgRadius READ getBgRadius WRITE setBgRadius)
//    Q_PROPERTY(int headRadius READ getHeadRadius WRITE setHeadRadius)

    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
//    Q_PROPERTY(QColor borderColorEnd READ getBorderColorEnd WRITE setBorderColorEnd)




public:
    explicit QBattery(QWidget *parent = 0);
    ~QBattery();

protected:
    void paintEvent(QPaintEvent *);
//    void drawBorder(QPainter *painter);
//    void drawBg(QPainter *painter);
//    void drawHead(QPainter *painter);

//private slots:
//    void updateValue();

private:
    QPropertyAnimation* barreryValueAnimation;
    double mMinValue = 0;                //电池电量最小值
    double mMaxValue = 100;                //电池电量最大值
    double mWarningValue;              //电池电量警戒值

    int mBorderWidth = 0;                //边框粗细
    int mBorderRadius;               //边框圆角角度
//    int bgRadius;                   //背景进度圆角角度
//    int headRadius;                 //头部圆角角度

    int mBatteryWidth = 0;                 //电池宽度
    int mBatteryHeight = 0;                //电池高度
    int mBatteryHeadWidth = 0;             //电池柱头宽度
    int mBatteryHeadHeight = 0;             //电池柱头宽度
    int mElectricBorder;                //电量填充边界
    int mAnimationMsecs;             //电池电量动画运行时间 单位毫秒

    QColor mBorderColor;        //边框渐变颜色
    QColor mWarningColorStart;         //电池低电量时的渐变开始颜色
    QColor mWarningColorEnd;           //电池低电量时的渐变结束颜色
    QColor mNormalColorStart;        //电池正常电量时的渐变开始颜色
    QColor mNormalColorEnd;          //电池正常电量时的渐变结束颜色

    double mCurrentValue;            //当前电量
//    QRectF batteryRect;             //电池主体区域
//    QTimer *timer;                  //绘制定时器
    void setValue(const double);  //设置电池电量


public:
    double minValue()            const;
    void setMinValue(double minValue);
    double maxValue()            const;
    void setMaxValue(double maxValue);

    double value()               const;
    double warningValue()          const;


//    double getStep()                const;
//    int getBorderWidth()            const;
//    int getBorderRadius()           const;
//    int getBgRadius()               const;
//    int getHeadRadius()             const;

    QColor borderColor()    const;
    void setBorderColor(const QColor &borderColor);//设置边框颜色
//    QColor getBorderColorEnd()      const;

    //设置电池电量报警时的渐变颜色
    QColor warningColorStart()     const;
    void setWarningColorStart(const QColor &warningColorStart);
    QColor warningColorEnd()       const;
    void setWarningColorEnd(const QColor &warningColorEnd);


    QColor normalColorStart()    const;
    void setNormalColorStart(const QColor &normalColorStart);
    QColor normalColorEnd()      const;
    void setNormalColorEnd(const QColor &normalColorEnd);

    int animationMsecs()     const;
    void setAnimationMsecs(const int animationMsecs);

//    QSize sizeHint()                const;
//    QSize minimumSizeHint()         const;

public Q_SLOTS:
//    //设置范围值
//    void setRange(double minValue, double maxValue);
//    void setRange(int minValue, int maxValue);



//    //设置电池电量值
    void setElecValue(int value);
    void setElecValue(double value);


    //设置电池电量警戒值
    void setWarningValue(double);
    void setWarningValue(int warningValue);

//    //设置步长
//    void setStep(double step);
//    void setStep(int step);

//    //设置边框粗细
//    void setBorderWidth(int borderWidth);
//    //设置边框圆角角度
//    void setBorderRadius(int borderRadius);
//    //设置背景圆角角度
//    void setBgRadius(int bgRadius);
//    //设置头部圆角角度
//    void setHeadRadius(int headRadius);


//    void setBorderColorEnd(const QColor &borderColorEnd);




Q_SIGNALS:
    void valueChanged(double value);

};

#endif // QBATTERY_H

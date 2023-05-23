#include "mainwindow.h"
#include"Location_t.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qRegisterMetaType<Location_t>("Location_t"); //将自己的类型注册到QT中
    qRegisterMetaType<QVector<QPointF>>("QVector<QPointF>");
    qRegisterMetaType<sensor_msgs::msg::Image::SharedPtr>("sensor_msgs::msg::Image::SharedPtr");
    w.show();
    return a.exec();
}

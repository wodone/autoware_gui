#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include<QComboBox>
#include<QToolBar>
#include<QGridLayout>
#include<QGroupBox>
#include<QTabWidget>
#include<QWidget>
#include<QTextEdit>
#include<QTextBrowser>
#include<QToolButton>
#include<QLineEdit>
#include<QPushButton>
#include<QDebug>
#include "QBattery.h"
#include<QLCDNumber>
#include "mySpeed.h"
#include<QOpenGLWidget>
#include<QGraphicsView>
#include<QProcess>
#include<QDir>
#include<QCheckBox>
#include<rclcpp/rclcpp.hpp>
#include"rclcom.h"
#include"mapItem.h"
#include<QGraphicsScene>
#include"steerWheel.h"
#include<QProgressBar>
#include<QListWidget>
#include<QLabel>
#include<QPixmap>
#include<QInputDialog>
#include"Mycar.h"
#include<QWindow>
#include<unistd.h>
#include<opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init_ui(); //初始化界面控件并且完成布局
    void init_time(); //初始化LCD时间控件
    void init_connect(); //初始化车辆相关信息信号和槽函数的连接
    void init_rviz(); //初始化rviz显示窗口
    void init_carRviz(); //初始化车辆周身rviz窗口


public slots:
    void onTimeOut(); //计时结束槽函数
    void onAction_addCamera();
    void update_camera(sensor_msgs::msg::Image::SharedPtr msgs); //展示地图信息
    void show_standardError(); //在控制台区域显示标准错误信息
    void show_standardOutput(); //在控制台区域显示标准输出信息
    void update_directionAndAngle(Location_t); //更新车身朝向和方向角
    void update_mainCamera(QPixmap pixmap); //更新主摄像头显示控件

private:
    Ui::MainWindow *ui;
    QAction* ac_select_point; //选择地图导航点
    QAction* ac_run; //启动autoware模块
    QAction* ac_stop; //停止autoware模块
    QAction* ac_runAll; //完全启动autoware
    QAction* ac_stopAll; //完全停止autoware
    QComboBox* comboBox_module; //autoware模块下拉栏
    QAction* ac_addCamera; //添加摄像头
    QAction* ac_setPort; //设置端口
    QToolBar* toolBar; //工具栏
    QGridLayout* layout_main; //全局主布局
    QWidget* con_carInfo; //车辆信息展示容器控件
    //QWidget* con_map; //地图区域的容器控件
    QTabWidget* con_com; //通信区域的容器控件
    QTabWidget* con_cam; //摄像头区域的容器控件
    QLabel* mainCamera; //主摄像头
    QTimer* timer_mainCamera; //主摄像头计时器
    Mat image;
    VideoCapture cap;
    //mainCameraWorking* mainCameraCom; //主摄像头通信类对象
    QWidget* con_control; //控制区域容器
    QWidget* con_up; //上方区域容器
    QWidget* con_rviz; //rviz展示控件
    QVector<QWidget*>cam; //摄像头显示区域控件数组
    QWidget* console; //命令行区域
    QLineEdit* console_input; //命令行输入区域
    QTextBrowser* console_output; //命令行输出区域
    QWidget* send; //车机通信发送消息区域
    QTextEdit* send_input; //消息输入区域
    QPushButton* send_buttonA; //利用不同方式发送消息，两个按钮
    QPushButton* send_buttonB;
    QBattery* battery; //电池显示控件
    QWidget* info; //信息显示区域控件
    QWidget* con_light; //转向灯和车辆档位显示容器
    QLabel* left_static; //静止状态左转向
    QLabel* right_static; //静止状态右转向
    QLabel* left_dynamic; //动态左转向
    QLabel* right_dynamic; //动态右转向
    QPixmap* left; //转向灯图片对象
    QPixmap* right;
    QPixmap* placeholder;
    QPixmap* left_back;
    QPixmap* right_back;
    QPixmap* img_park;
    QPixmap* img_back;
    QPixmap* img_advance;
    QPixmap* img_romote;
    QLabel* gearShow;
    QLabel* controlShow;
    QTimer* timer_left; //转向灯闪烁定时器
    QTimer* timer_right;
    QLabel* gear_P;//汽车档位
    QLabel* gear_R;
    QLabel* gear_N;
    QLabel* gear_D;
    QListWidget* info_items; //信息项
    QListWidgetItem* info_item_speed; //速度信息
    QListWidgetItem* info_item_ele; //海拔信息
    QListWidgetItem* info_item_latitude; //经纬度信息
    QListWidgetItem* info_item_angle_yaw; //方位角信息
    QListWidgetItem* info_item_angle_pitch;
    QListWidgetItem* info_item_angle_roll;
    QListWidgetItem* info_item_steer; //方向盘转角
    QListWidgetItem* info_item_direction; //车身朝向
    QLCDNumber* time; //当前时间显示
    MySpeed* speed; //车辆速度仪表盘显示
    steerWheel* steer; //方向盘显示
    //QGraphicsView* map; //地图数据显示
    //QGraphicsScene* scene_map; //地图数据的scene
    //mapItem* Item_map; //地图的Item
    QProcess* console_exec; //控制台命令执行器
    QDir* workDir; //程序工作目录
    rclcom* communicate; //通信类
    QVector<QString> cameraMap; //摄像机表
    Mycar* mycar; //车辆俯视图和超声波雷达
    QTabWidget* AroundCar;
    QProcess* Process_lanuch_A; //控制车辆周围Rviz视图的QProcess
    QProcess* Process_lanuch_B; //控制高精度地图显示和轨迹的QProcess
    QToolButton* tool_start;
    QToolButton* tool_pause;
    QToolButton* tool_stop;
    QLabel* label_model;
    QLabel* label_light;
    QLabel* label_speed;
    QLabel* label_error;
};
#endif // MAINWINDOW_H

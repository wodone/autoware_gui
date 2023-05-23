#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QIcon>
#include<QTime>
#include<QTimer>
#include<QProcess>
#include<QString>
#include<QStringList>
#include<QDir>
#include<stdlib.h>
#include<QCheckBox>
#include<QMessageBox>
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::Window | Qt::FramelessWindowHint|
//                   Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint);
    setWindowIcon(QIcon(":/windows/Icon/windowsIcon.png"));
    communicate=new rclcom;
    communicate->start();
    Process_lanuch_A=new QProcess(this);
    Process_lanuch_B=new QProcess(this);
    //mainCameraCom=new mainCameraWorking(this);
    timer_mainCamera=new QTimer(this);
    init_ui();
    init_connect();
    init_rviz();
    init_carRviz();
    this->showMaximized(); // 最大化窗口
    cap.open(0); //打开摄像头
    if(cap.isOpened()) timer_mainCamera->start(30);
    else QMessageBox::critical(this,"错误","没有检测到主摄像头！");
}

MainWindow::~MainWindow()
{
    //利用信号杀死rviz进程
//    Process_lanuch_A->kill();
//    Process_lanuch_B->kill();
    system("pkill rviz2"); //杀死所有rviz2残留进程
    delete left; //释放资源
    delete right;
    delete placeholder;
    delete ui;
}

void MainWindow::init_carRviz(){
    qDebug()<<"启动！";
    QProcess* Process_hide = new QProcess(this);
    Process_lanuch_A->start("/home/ros2/autoware_gui_ws/rviz_car.sh");
    sleep(2);
    //Process_hide->startDetached("/home/ros2/autoware_gui_ws/hide.sh");
    //开始寻找winID
    QProcess* find_list=new QProcess(this);
    find_list->start("wmctrl -l");
    find_list->waitForReadyRead();
    QString output=(QString)find_list->readAllStandardOutput();
    auto list=output.split('\n');
    list.pop_back();
    QString str_winId;
    bool ok_rviz=false;
    for(QString it:list){
        qDebug()<<it;
        if(it.contains("RViz")){
            str_winId=it.mid(0,10);
            ok_rviz=true;
            break;
        }
        else continue;
    }
    qDebug()<<str_winId;
    if(ok_rviz){
        bool ok;
        int winId=str_winId.toInt(&ok,16);
        if(ok){
              auto rvizWindow=QWindow::fromWinId((WId)winId);
              con_rviz=QWidget::createWindowContainer(rvizWindow,this,Qt::Widget);
              rvizWindow->setFlags(Qt::Window | Qt::FramelessWindowHint|
                                   Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint);
              AroundCar->addTab(con_rviz,QIcon(":/windows/Icon/lidar.png"),"激光雷达");
              AroundCar->setCurrentIndex(1);
        }
        else{
            QMessageBox::critical(this,"错误","Rviz窗口id转换错误！");
            return;
        }
    }
    else{
        QMessageBox::critical(this,"错误","Rviz没有正常启动，请重试！");
        return;
    }
}

void MainWindow::init_rviz(){
    qDebug()<<"启动！";
    QProcess* Process_hide = new QProcess(this);
    Process_lanuch_B->start("/home/ros2/autoware_gui_ws/rviz_localization.sh");
    sleep(2);
    //Process_hide->startDetached("/home/ros2/autoware_gui_ws/hide.sh");
    //开始寻找winID
    for(int i=0;i<2;i++){
        QProcess* find_list=new QProcess(this);
        find_list->start("wmctrl -l");
        find_list->waitForReadyRead();
        QString output=(QString)find_list->readAllStandardOutput();
        auto list=output.split('\n');
        list.pop_back();
        QString str_winId;
        bool ok_rviz=false;
        for(QString it:list){
            qDebug()<<it;
            if(it.contains("RViz")){
                str_winId=it.mid(0,10);
                ok_rviz=true;
                break;
            }
            else continue;
        }
        qDebug()<<str_winId;
        if(ok_rviz){
            bool ok;
            int winId=str_winId.toInt(&ok,16);
            if(ok){
                  auto rvizWindow=QWindow::fromWinId((WId)winId);
                  con_rviz=QWidget::createWindowContainer(rvizWindow,this,Qt::Widget);
                  rvizWindow->setFlags(Qt::Window | Qt::FramelessWindowHint|
                                       Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint);
                  layout_main->addWidget(con_rviz,1,3,1,1);
            }
            else{
                QMessageBox::critical(this,"错误","Rviz窗口id转换错误！");
                return;
            }
        }
        else{
            QMessageBox::critical(this,"错误","Rviz没有正常启动，请重试！");
            return;
        }
        sleep(1);
    }
}


void MainWindow::init_ui(){
    /*
     * 初始化工具栏
    */
    toolBar=this->addToolBar("tools");
    //ac_select_point=new QAction(QIcon("://Icon/Button/select.png"),tr("选择导航点"),this);
    ac_run=new QAction(QIcon(":/Icon/Button/run.png"),tr("运行"),this);
    ac_stop=new QAction(QIcon(":/Icon/Button/stop.png"),tr("停止"),this);
    ac_runAll=new QAction(QIcon(":/Icon/Button/run_all.png"),tr("整体运行autoware"),this);
    ac_stopAll=new QAction(QIcon(":/Icon/Button/stop_all.png"),tr("停止autoware"),this);
    ac_addCamera=new QAction(QIcon(":/Icon/Button/camera.png"),tr("添加摄像头"),this);
    ac_setPort=new QAction(QIcon(":/windows/Icon/set.png"),"设置超声波雷达端口映射",this);
    comboBox_module=new QComboBox(this);
    comboBox_module->addItem(QIcon(":/Icon/Icon/Icon/data.png"),"Data Processing");
    comboBox_module->addItem(QIcon(":/Icon/Icon/Icon/perception.png"),"Perception");
    comboBox_module->addItem(QIcon(":/Icon/Icon/Icon/Localization.png"),"Localization");
    comboBox_module->addItem(QIcon(":/Icon/Icon/Icon/planning.png"),"Planning");
    comboBox_module->addItem(QIcon(":/Icon/Icon/Icon/control.png"),"Vehicle Control");
    toolBar->addAction(ac_runAll);
    toolBar->addAction(ac_stopAll);
    toolBar->addSeparator(); //添加分割线
    toolBar->addSeparator();
    toolBar->addAction(ac_run);
    toolBar->addAction(ac_stop);
    toolBar->addWidget(comboBox_module);
    toolBar->addSeparator(); //添加分割线
    toolBar->addSeparator();
    toolBar->addAction(ac_addCamera);
    toolBar->addSeparator();
    toolBar->addSeparator();
    toolBar->addAction(ac_setPort);
    toolBar->hide();
    //toolBar->addAction(ac_select_point);
    /*
     * 初始化主窗口布局
     * 实例化主窗口布局，主窗口采用QMap<QString,rclcom*>sub_map; //订阅者表GridLayout（网格化布局）
     * 行比例为2：1，列比例为1：1:1:1
    */
    layout_main=new QGridLayout(this);
    layout_main->setRowStretch(0,1); //设置行比例
    layout_main->setRowStretch(1,1);
    layout_main->setColumnStretch(0,1); //设置列比例
    layout_main->setColumnStretch(1,1);
    layout_main->setColumnStretch(2,1);
    layout_main->setColumnStretch(3,1);
    /*
     * 实例化容器控件，并且添加到主窗口布局
    */
    con_carInfo=new QWidget(this);
    //con_map=new QWidget(this);
    //con_rviz=new QWidget(this);
    con_cam=new QTabWidget(this);
    con_cam->setTabsClosable(true);
    con_com=new QTabWidget(this);
    //mycar=new Mycar(this);
    AroundCar=new QTabWidget(this);
    layout_main->addWidget(AroundCar,1,0,1,1);
    //AroundCar->addTab(mycar,QIcon(":/windows/Icon/ultrasonic.png"),"超声波雷达");
    layout_main->addWidget(con_carInfo,1,1,1,2);
    //con_carInfo->hide();
    //layout_main->addWidget(con_com,1,0,1,1);
    con_com->hide();
    //layout_main->addWidget(con_cam,0,0,1,4);
    con_cam->hide();
    mainCamera=new QLabel(this);
    mainCamera->setScaledContents(true);
    con_control=new QWidget(this);
    con_up=new QWidget(this);
    layout_main->addWidget(con_up,0,0,1,4);
    auto temp_layout_up=new QGridLayout(this);
    temp_layout_up->setRowStretch(0,5);
    temp_layout_up->setRowStretch(1,1);
    temp_layout_up->addWidget(mainCamera,0,0,2,1);
    //temp_layout_up->addWidget(con_control,1,0,1,1);
    con_up->setLayout(temp_layout_up);
    ui->centralwidget->setLayout(layout_main); //设置主窗口布局
    /*
     * 实例化显示部件
    */
//    auto temp=new QWidget(this);
//    cam.push_back(temp);
//    con_cam->addTab(temp,QIcon(":/Icon/Icon/Icon/cam.png"),"摄像头1");
    console=new QWidget(this);
    send=new QWidget(this);
    console_input=new QLineEdit(console);
    console_output=new QTextBrowser(console);
    console_exec=new QProcess(this); //实例化命令处理器
    workDir=new QDir(QCoreApplication::applicationDirPath()); //实例化工作目录
    console_output->append(workDir->path()+">>"); //初始控制台信息
    send_input=new QTextEdit(send);
    send_buttonA=new QPushButton(QIcon(":/Icon/Button/sendA.png"),"V2I",send);
    send_buttonB=new QPushButton(QIcon(":/Icon/Button/sendB.png"),"V2V",send);
    auto temp_layout_console=new QGridLayout(console); //临时布局
    auto temp_layout_send=new QGridLayout(send);
    temp_layout_console->setRowStretch(0,1); //设置行比例为1：9
    temp_layout_console->setRowStretch(1,10);
    temp_layout_send->setRowStretch(0,1); //设置行比例为1：1
    temp_layout_send->setRowStretch(1,1);
    temp_layout_send->setColumnStretch(0,5);//设置列比例为5：1
    temp_layout_send->setColumnStretch(1,1);
    temp_layout_console->addWidget(console_input,0,0,1,1);
    temp_layout_console->addWidget(console_output,1,0,1,1);
    temp_layout_send->addWidget(send_input,0,0,2,1);
    temp_layout_send->addWidget(send_buttonA,0,1,1,1);
    temp_layout_send->addWidget(send_buttonB,1,1,1,1);
    console->setLayout(temp_layout_console);
    send->setLayout(temp_layout_send);
    con_com->addTab(console,QIcon(":/Icon/Icon/Icon/console.png"),"控制台");
    con_com->addTab(send,QIcon(":/Icon/Icon/Icon/send.png"),"Message");
    auto temp_layout_carInfo=new QGridLayout(con_carInfo); //车辆信息临时布局
    temp_layout_carInfo->setColumnStretch(0,2); //设置列比例为1：1：1：1
    temp_layout_carInfo->setColumnStretch(1,1);
    temp_layout_carInfo->setColumnStretch(2,1);
    temp_layout_carInfo->setColumnStretch(3,2);
    temp_layout_carInfo->setRowStretch(0,1);
    temp_layout_carInfo->setRowStretch(1,1);
    temp_layout_carInfo->setRowStretch(2,1);
    left=new QPixmap(":/widget/Icon/Widget/left.png"); //加载图片
    right=new QPixmap(":/widget/Icon/Widget/right.png");
    placeholder=new QPixmap(":/widget/Icon/Widget/placeholder.png");
    left_back=new QPixmap(":/widget/Icon/Widget/left.png");
    right_back=new QPixmap(":/widget/Icon/Widget/right.png");
    img_park=new QPixmap(":/Image/Icon/Image/park.png");
    img_back=new QPixmap(":/Image/Icon/Image/back.png");
    img_advance=new QPixmap(":/Image/Icon/Image/advance.png");
    img_romote=new QPixmap(":/Image/Icon/Image/remote_control.png");
    QPixmap sourceImage_left(":/widget/Icon/Widget/left.png");
    QPainter painter(left_back);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(left_back->rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, sourceImage_left);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(left_back->rect(), QColor(0, 0, 0, 128));
    painter.end();
    QPixmap sourceImage_right(":/widget/Icon/Widget/right.png");
    QPainter painter2(right_back);
    painter2.setCompositionMode(QPainter::CompositionMode_Source);
    painter2.fillRect(right_back->rect(), Qt::transparent);
    painter2.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter2.drawPixmap(0, 0, sourceImage_right);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter2.fillRect(right_back->rect(), QColor(0, 0, 0, 128));
    painter2.end();
    con_light=new QWidget(con_carInfo);
    left_static=new QLabel(con_carInfo);
    right_static=new QLabel(con_carInfo);
    left_dynamic=new QLabel(con_carInfo);
    right_dynamic=new QLabel(con_carInfo);
//    gearShow=new QLabel(con_carInfo);
//    controlShow=new QLabel(con_carInfo);
    left->scaled(left_dynamic->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation); //设置图片适应控件大小
    right->scaled(right_dynamic->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //placeholder->scaled(left_static->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    left_back->scaled(left_static->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    right_back->scaled(right_static->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    img_park->scaled(gearShow->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    img_back->scaled(gearShow->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    img_advance->scaled(gearShow->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    img_romote->scaled(controlShow->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    left_static->setScaledContents(true);
    right_static->setScaledContents(true);
    left_dynamic->setScaledContents(true);
    right_dynamic->setScaledContents(true);
    //gearShow->setScaledContents(true);
    //controlShow->setScaledContents(true);
    left_static->setPixmap(*left_back);
    right_static->setPixmap(*right_back);
    left_dynamic->setPixmap(*left);
    right_dynamic->setPixmap(*right);
    //gearShow->setPixmap(*img_park);
    //controlShow->setPixmap(*img_romote);
    gear_P=new QLabel(con_carInfo);
    gear_R=new QLabel(con_carInfo);
    gear_N=new QLabel(con_carInfo);
    gear_D=new QLabel(con_carInfo);
    gear_P->setText("P"); //初始化为停车档
    gear_P->setStyleSheet("background-color:rgb(193,210,240);");
    gear_R->setText("R");
    gear_N->setText("N");
    gear_D->setText("D");
    QWidget* con_gear=new QWidget(this);
    auto temp_layout_gear=new QGridLayout(this);
    for(int i=0;i<4;i++) temp_layout_gear->setRowStretch(i,1);
    temp_layout_gear->addWidget(gear_P,0,0,1,1);
    temp_layout_gear->addWidget(gear_R,1,0,1,1);
    temp_layout_gear->addWidget(gear_N,2,0,1,1);
    temp_layout_gear->addWidget(gear_D,3,0,1,1);
    con_gear->setLayout(temp_layout_gear);
    //..在此处将档位槽函数进行连接
    timer_left = new QTimer(this);
    timer_right = new QTimer(this);
    left_dynamic->hide();
    right_dynamic->hide();
    //..在此处将转向灯变换的槽函数进行连接
    auto temp_layout_light=new QGridLayout(this);
    temp_layout_light->setColumnStretch(0,1);
    temp_layout_light->setColumnStretch(1,1);
    temp_layout_light->setColumnStretch(2,1);
    temp_layout_light->addWidget(left_static,0,0,1,1);
    temp_layout_light->addWidget(right_static,0,2,1,1);
    temp_layout_light->addWidget(left_dynamic,0,0,1,1);
    temp_layout_light->addWidget(right_dynamic,0,2,1,1);
    //temp_layout_light->addWidget(controlShow,0,0,1,1);
    //temp_layout_light->addWidget(gearShow,0,2,1,1);
    temp_layout_light->addWidget(con_gear,0,1,1,1);
    con_light->setLayout(temp_layout_light);
    temp_layout_carInfo->addWidget(con_light,2,1,1,2);
    temp_layout_carInfo->addWidget(con_control,0,0,1,4);
    battery=new QBattery(this);
    temp_layout_carInfo->addWidget(battery,1,0,1,1);
    //toolBar->addWidget(battery);
    info=new QWidget(con_carInfo);
    temp_layout_carInfo->addWidget(info,1,3,2,2);
    auto temp_layout_info=new QGridLayout(this);
    temp_layout_info->setRowStretch(0,1);
    temp_layout_info->setRowStretch(1,1);
    temp_layout_info->setRowStretch(2,1);
    info_items=new QListWidget(this);
    temp_layout_info->addWidget(info_items,0,0,3,1);
    info_item_speed=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/speed.png"),"0.0 km/h");
    info_item_latitude=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/longitude_latitude.png"),"N38°39′27.97″E104°04′58.66″");
    info_item_ele=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/elevation.png"),"2025m");
//    info_item_angle_yaw=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/angel.png"),"方向角--yaw");
//    info_item_angle_pitch=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/angel.png"),"方向角--pitch");
//    info_item_angle_roll=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/angel.png"),"方向角--roll");
    info_item_steer=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/steer.png"),"方向盘转角");
    //info_item_direction=new QListWidgetItem(QIcon(":/Icon/Icon/Icon/direction.png"),"车身朝向");
    info_item_speed->setFlags(info_item_speed->flags() & ~Qt::ItemIsSelectable);
    info_item_latitude->setFlags(info_item_latitude->flags() & ~Qt::ItemIsSelectable);
    info_item_ele->setFlags(info_item_ele->flags() & ~Qt::ItemIsSelectable);
//    info_item_angle_yaw->setFlags(info_item_angle_yaw->flags() & ~Qt::ItemIsSelectable);
//    info_item_angle_pitch->setFlags(info_item_angle_pitch->flags() & ~Qt::ItemIsSelectable);
//    info_item_angle_roll->setFlags(info_item_angle_roll->flags() & ~Qt::ItemIsSelectable);
    info_item_steer->setFlags(info_item_steer->flags() & ~Qt::ItemIsSelectable);
    //info_item_direction->setFlags(info_item_steer->flags() & ~Qt::ItemIsSelectable);
    info_items->addItem(info_item_speed);
    //info_items->addItem(info_item_direction);
    info_items->addItem(info_item_latitude);
    info_items->addItem(info_item_ele);
//    info_items->addItem(info_item_angle_yaw);
//    info_items->addItem(info_item_angle_pitch);
//    info_items->addItem(info_item_angle_roll);
    info_items->addItem(info_item_steer);
    info->setLayout(temp_layout_info);
    time=new QLCDNumber(con_carInfo);
    init_time(); //初始化时间控件
    temp_layout_carInfo->addWidget(time,2,0,1,1);
    time->setFrameStyle(QFrame::NoFrame);
    steer=new steerWheel(con_carInfo);
    temp_layout_carInfo->addWidget(steer,1,1,1,1);
    speed=new MySpeed(con_carInfo);
    temp_layout_carInfo->addWidget(speed,1,2,1,1);
    con_carInfo->setLayout(temp_layout_carInfo);
//    auto temp_layout_map=new QGridLayout(con_map);
//    for(int i=0;i<10;i++) temp_layout_map->setRowStretch(i,1);
//    for(int i=0;i<20;i++) temp_layout_map->setColumnStretch(i,1);
//    //map=new QGraphicsView(this);
//    temp_layout_map->addWidget(map,0,0,10,20);
//    temp_layout_map->addWidget(speed,1,1,2,2);
//    temp_layout_map->addWidget(steer,1,3,2,2);
//    temp_layout_map->addWidget(con_light,3,1,2,4);
    //scene_map=new QGraphicsScene(this);
    //scene_map->clear(); //清空场景类
    //Item_map=new mapItem();
//    scene_map->addItem(Item_map); //向地图场景中添加地图项
//    map->setScene(scene_map); //设置地图视图的场景
    auto temp_layout_control=new QGridLayout(this);
    temp_layout_control->setRowStretch(0,1);
    temp_layout_control->setRowStretch(1,1);
    temp_layout_control->setColumnStretch(0,1);
    temp_layout_control->setColumnStretch(1,1);
    temp_layout_control->setColumnStretch(2,1);
    temp_layout_control->setColumnStretch(3,1);
    temp_layout_control->setColumnStretch(4,30);
    tool_stop=new QToolButton(this);
    tool_start=new QToolButton(this);
    tool_pause=new QToolButton(this);
    label_model=new QLabel(this);
    label_error=new QLabel(this);
    label_light=new QLabel(this);
    //label_speed=new QLabel(this);
    tool_start->setIcon(QIcon(":/Icon/Button/run_all.png"));
    tool_stop->setIcon(QIcon(":/Icon/Button/stop_all.png"));
    tool_pause->setIcon(QIcon(":/Icon/pause.png"));
    label_light->setPixmap(QPixmap(":/Icon/green.png"));
    //label_model->setStyleSheet(QString("background-color:") + "blue");
    label_error->setStyleSheet(QString("background-color:") + "rgb(189,252,201)");
    temp_layout_control->addWidget(tool_start,0,0,1,1);
    temp_layout_control->addWidget(tool_pause,0,1,1,1);
    temp_layout_control->addWidget(tool_stop,0,2,1,1);
    temp_layout_control->addWidget(label_light,0,3,1,1);
    temp_layout_control->addWidget(label_model,0,4,1,1);
    temp_layout_control->addWidget(label_error,1,0,1,5);
    QFont font("Microsoft YaHei", 20, 75);
    label_error->setFont(font);
    label_error->setAlignment(Qt::AlignCenter);
    label_error->setText("没有发现任何问题！");
    QFont font2("Microsoft YaHei",10,75);
    label_model->setFont(font2);
    label_model->setText("自动驾驶模式");
    con_control->setLayout(temp_layout_control);
}

void MainWindow::init_connect(){
    connect(ac_addCamera,SIGNAL(triggered()),this,SLOT(onAction_addCamera()));
    connect(timer_mainCamera,&QTimer::timeout,[&](){
        cap>>image; //读取一帧图像
        cvtColor(image,image,COLOR_BGR2RGB); //色彩格式转换
        QPixmap pixmap;
        pixmap=QPixmap::fromImage(QImage(image.data,image.cols,image.rows,QImage::Format_RGB888)); //转换为QPixmap格式
        pixmap.scaled(mainCamera->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation); //图片自适应控件大小
        mainCamera->setPixmap(pixmap);
    });
    //connect(communicate,SIGNAL(signal_revSimpleMap(QImage)),Item_map,SLOT(updateMap(QImage))); //连接地图绘制信号和更新地图槽函数
//    connect(communicate,SIGNAL(signal_revLocation(Location_t)),Item_map,SLOT(updateLocation(Location_t))); //连接车辆位置绘制信号和槽函数
//    connect(communicate,SIGNAL(signal_revLocation(Location_t)),this,SLOT(update_directionAndAngle(Location_t))); //连接车辆信息更新信息和槽函数
//    connect(communicate,SIGNAL(signal_revPath(QVector<QPointF>)),Item_map,SLOT(updatePath(QVector<QPointF>))); //连接路径绘制信号和槽函数
    //connect(ac_runAll,SIGNAL(triggered()),this,SLOT(init_rviz()));
    connect(console_exec,SIGNAL(readyReadStandardError()),SLOT(show_standardError())); //将执行器准备好读取的信号和显示槽函数进行连接
    connect(console_exec,SIGNAL(readyReadStandardOutput()),SLOT(show_standardOutput()));
    connect(communicate,SIGNAL(signal_revImage(sensor_msgs::msg::Image::SharedPtr)),SLOT(update_camera(sensor_msgs::msg::Image::SharedPtr)));
    connect(console_input,&QLineEdit::returnPressed,this,[&](){ //将控制台输入信号和处理槽函数绑定
        //qDebug()<<workDir->path();
        auto input=(console_input->text()).split(" ");
        auto cmd=input.first(); //指令
        auto para=input; //参数
        para.removeFirst();
        if(cmd=="cd"){ //改变工作目录
            if(para[0]==".."){
                workDir->cdUp(); //向上级目录移动
                QDir::setCurrent(workDir->path()); //改变程序实际运行工作目录
                console_output->append(workDir->path()+">>");
                console_input->clear();
                return; //地图区域的容器控件
            }
            else{
                if(workDir->exists(para[0])){ //想要移动的工作目录确实存在
                    workDir->setPath(para[0]); //改变工作目录
                    QDir::setCurrent(workDir->path());
                    console_output->append(workDir->path()+">>");
                    console_input->clear();
                    return;
                }
                else{
                    console_output->append("不存在目录"+para[0]);
                    console_output->append(workDir->path()+">>");
                    console_input->clear();
                    return;
                }
            }
        }
        console_exec->start(cmd,para); //启动指令执行器
        console_input->clear();
    });
    connect(timer_left,&QTimer::timeout,this,[=](){
        if(left_dynamic->isHidden()) left_dynamic->show();
        else left_dynamic->hide();
    });
    connect(timer_right,&QTimer::timeout,this,[=](){
        if(right_dynamic->isHidden()) right_dynamic->show();
        else right_dynamic->hide();
    });
}

void MainWindow::update_directionAndAngle(Location_t location){
    //qDebug()<<"方向更新！";
//    info_item_direction->setText(QString::number(location.yaw)); //更新车辆朝向
//    info_item_angle_yaw->setText("yaw:"+QString::number(location.yaw)); //更新方向角度
//    info_item_angle_pitch->setText("pitch:"+QString::number(location.pitch)); //更新方向角度
//    info_item_angle_roll->setText("roll:"+QString::number(location.roll)); //更新方向角度
}

void MainWindow::update_mainCamera(QPixmap pixmap){
    qDebug()<<"主摄像头图像更新";
    mainCamera->setPixmap(pixmap); //更新控件
}

void MainWindow::init_time(){
    time->setDigitCount(8); // 设置能显示的位数
    QTimer *pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    pTimer->start();
}

void MainWindow::onTimeOut(){
    auto currentTime=QTime::currentTime(); //获取当前时间
    time->display(currentTime.toString("hh:mm:ss"));
}

void MainWindow::show_standardError(){
    console_output->append(console_exec->readAllStandardError());
    console_output->append(workDir->path()+">>");
}

void MainWindow::show_standardOutput(){
    console_output->append(console_exec->readAllStandardOutput());
    console_output->append(workDir->path()+">>");
}

void MainWindow::update_camera(sensor_msgs::msg::Image::SharedPtr msgs){
    QString frame_id=QString::fromStdString(msgs->header.frame_id);
    int index=-1;
    for(int i=0;i<cameraMap.size();i++){ //在数组中查找该摄像头信息所在的控件索引
        if(cameraMap[i]==frame_id){
            index=i;
            break;
        }
        else continue;
    }
    if(index!=-1){
        auto label=(QLabel*)con_cam->widget(index); //找到控件索引页
//        qDebug()<<"找到frame_id";
//        qDebug()<<"在"<<index<<"页面作更改";
        //QPixmap pixmap=Utilities::rosImage_to_QPixmap(msgs);
        label->setScaledContents(true);
        //label->setPixmap(pixmap.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else{
        cameraMap.push_back(frame_id); //将摄像头加入到表
        index=cameraMap.size()-1;
        auto label=(QLabel*)con_cam->widget(index);
//        qDebug()<<"没有找到frame_id";
//        qDebug()<<"在"<<index<<"页面作更改";
        //QPixmap pixmap=Utilities::rosImage_to_QPixmap(msgs);
        label->setScaledContents(true);
        //label->setPixmap(pixmap.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}

void MainWindow::onAction_addCamera(){
    bool ok=false;
    QString cameraName = QInputDialog::getText(this, "添加摄像头","请输入摄像头名称",QLineEdit::Normal,"", &ok);
    if(ok&&!cameraName.isEmpty()){
        QProcess tempProcess; //开始获取ros2消息列表
        tempProcess.start("ros2 topic list");
        tempProcess.waitForStarted();
        tempProcess.waitForFinished();
        QString topicList=tempProcess.readAllStandardOutput();
        //qDebug()<<topicList;
        QStringList list=topicList.split('\n');
        list.removeLast();
        bool ok2=false;
        QString topicName=QInputDialog::getItem(this,"选择消息","请选择需要订阅的消息",list,0,true,&ok2);
        if(ok2&&!topicName.isEmpty()){
            auto label=new QLabel(this);
            con_cam->addTab(label,QIcon(":/Icon/Icon/Icon/cam.png"),cameraName);
            communicate->addCamera(cameraName,topicName);
        }
        else return;
        //qDebug()<<tempProcess.readAllStandardOutput();
    }
    else return;
}


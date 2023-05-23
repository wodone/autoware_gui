#include "Mycar.h"
#include<QDebug>

Mycar::Mycar(QWidget *parent) : QWidget(parent)
{
    //测试代码
    for(int i=0;i<20;i++) radarTypeMap.insert(i,0);
}

void Mycar::paintEvent(QPaintEvent *event){
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing); //设置抗锯齿
    drawMain();
    drawAllRadar();
    painter.end();
}

void Mycar::drawMain(){
    QPen pen(color_car);
    pen.setWidth(2);
    painter.setPen(pen);
    qDebug()<<"绘制车辆";
    //绘画车辆俯视图多边形
    double width=this->width*ratio;
    double height=this->height*ratio;
    double gap=this->gap*ratio;
    points[0]=leftTop;
    points[1]=QPointF(points[0].x()-gap,points[0].y()+gap);
    points[2]=QPointF(points[1].x(),points[1].y()+height);
    points[3]=QPointF(points[2].x()+gap,points[2].y()+gap);
    points[4]=QPointF(points[3].x()+width,points[3].y());
    points[5]=QPointF(points[2].x()+gap*2+width,points[2].y());
    points[6]=QPointF(points[1].x()+gap*2+width,points[1].y());
    points[7]=QPointF(points[0].x()+width,points[0].y());
    painter.drawPolygon(points,8);
    pen.setColor(color_radar);
    pen.setWidth(4);
    painter.setPen(pen);
    //绘制超声波雷达点
    points_radar[0]=QPointF(points[0].x()+width/3,points[0].y());
    points_radar[1]=QPointF(points[7].x()-width/3,points[0].y());
    points_radar[2]=QPointF(points[0].x()-gap/2,points[0].y()+gap/2);
    points_radar[3]=QPointF(points[7].x()+gap/2,points[7].y()+gap/2);
    points_radar[4]=points[1];
    points_radar[5]=points[6];
    points_radar[6]=QPointF(points[1].x(),points[1].y()+height/5);
    points_radar[7]=QPointF(points[6].x(),points[6].y()+height/5);
    points_radar[8]=QPointF(points_radar[6].x(),points_radar[6].y()+height/5);
    points_radar[9]=QPointF(points_radar[7].x(),points_radar[7].y()+height/5);
    points_radar[10]=QPointF(points_radar[8].x(),points_radar[8].y()+(height/5));
    points_radar[11]=QPointF(points_radar[9].x(),points_radar[9].y()+(height/5));
    points_radar[12]=QPointF(points_radar[6].x(),points_radar[6].y()+(height/5)*2+height/5);
    points_radar[13]=QPointF(points_radar[7].x(),points_radar[7].y()+(height/5)*2+height/5);
    points_radar[14]=QPointF(points_radar[4].x(),points_radar[4].y()+height);
    points_radar[15]=QPointF(points_radar[5].x(),points_radar[5].y()+height);
    points_radar[16]=QPointF(points_radar[2].x(),points_radar[2].y()+height+gap);
    points_radar[17]=QPointF(points_radar[3].x(),points_radar[3].y()+height+gap);
    points_radar[18]=QPointF(points_radar[0].x(),points_radar[0].y()+height+gap*2);
    points_radar[19]=QPointF(points_radar[1].x(),points_radar[1].y()+height+gap*2);
    for(int i=0;i<20;i++) painter.drawPoint(points_radar[i]);
//    for(int i=0;i<20;i++) drawRadar(points_radar[i],0);
    isDrawMain=true;
    getLocationMap(); //得到超声波雷达位置表
}

void Mycar::drawRadar(std::shared_ptr<radarLocation> rectangle,int type,int direction){
    QPen pen;
    pen.setWidth(2);
    switch(type){
    case 0:{
        pen.setColor(Qt::green);
        painter.setPen(pen);
        switch(direction){
        case 0:{
            painter.drawArc(rectangle->down,60*16,60*16);
            painter.drawArc(rectangle->mid,45*16,90*16);
            painter.drawArc(rectangle->up,30*16,120*16);
            break;
        }
        case 1:{
            painter.drawArc(rectangle->down,-60*16,-60*16);
            painter.drawArc(rectangle->mid,-45*16,-90*16);
            painter.drawArc(rectangle->up,-30*16,-120*16);
            break;
        }
        case 2:{
            painter.drawArc(rectangle->down,-150*16,-60*16);
            painter.drawArc(rectangle->mid,-135*16,-90*16);
            painter.drawArc(rectangle->up,-120*16,-120*16);
            break;
        }
        case 3:{
            painter.drawArc(rectangle->down,-30*16,60*16);
            painter.drawArc(rectangle->mid,-45*16,90*16);
            painter.drawArc(rectangle->up,-60*16,120*16);
            break;
        }
        case 4:{
            painter.drawArc(rectangle->down,165*16,-60*16);
            painter.drawArc(rectangle->mid,180*16,-90*16);
            painter.drawArc(rectangle->up,-165*16,-120*16);
            break;
        }
        case 5:{
            painter.drawArc(rectangle->down,15*16,60*16);
            painter.drawArc(rectangle->mid,0,90*16);
            painter.drawArc(rectangle->up,-15*16,120*16);
            break;
        }
        case 6:{
            painter.drawArc(rectangle->down,-105*16,-60*16);
            painter.drawArc(rectangle->mid,-90*16,-90*16);
            painter.drawArc(rectangle->up,-75*16,-120*16);
            break;
        }
        case 7:{
            painter.drawArc(rectangle->down,-15*16,-60*16);
            painter.drawArc(rectangle->mid,0,-90*16);
            painter.drawArc(rectangle->up,15*16,-120*16);
            break;
        }
        }
        break;
    }
    case 1:{
        pen.setColor(Qt::green);
        painter.setPen(pen);
        switch(direction){
        case 0:{
            painter.drawArc(rectangle->down,60*16,60*16);
            painter.drawArc(rectangle->mid,45*16,90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,30*16,120*16);
            break;
        }
        case 1:{
            painter.drawArc(rectangle->down,-60*16,-60*16);
            painter.drawArc(rectangle->mid,-45*16,-90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-30*16,-120*16);
            break;
        }
        case 2:{
            painter.drawArc(rectangle->down,-150*16,-60*16);
            painter.drawArc(rectangle->mid,-135*16,-90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-120*16,-120*16);
            break;
        }
        case 3:{
            painter.drawArc(rectangle->down,-30*16,60*16);
            painter.drawArc(rectangle->mid,-45*16,90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-60*16,120*16);
            break;
        }
        case 4:{
            painter.drawArc(rectangle->down,165*16,-60*16);
            painter.drawArc(rectangle->mid,180*16,-90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-165*16,-120*16);
            break;
        }
        case 5:{
            painter.drawArc(rectangle->down,15*16,60*16);
            painter.drawArc(rectangle->mid,0,90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-15*16,120*16);
            break;
        }
        case 6:{
            painter.drawArc(rectangle->down,-105*16,-60*16);
            painter.drawArc(rectangle->mid,-90*16,-90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,-75*16,-120*16);
            break;
        }
        case 7:{
            painter.drawArc(rectangle->down,-15*16,-60*16);
            painter.drawArc(rectangle->mid,0,-90*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->up,15*16,-120*16);
            break;
        }
        }
        break;
    }
    case 2:{
        pen.setColor(Qt::green);
        painter.setPen(pen);
        switch(direction){
        case 0:{
            painter.drawArc(rectangle->down,60*16,60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,45*16,90*16);
            painter.drawArc(rectangle->up,30*16,120*16);
            break;
        }
        case 1:{
            painter.drawArc(rectangle->down,-60*16,-60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,-45*16,-90*16);
            painter.drawArc(rectangle->up,-30*16,-120*16);
            break;
        }
        case 2:{
            painter.drawArc(rectangle->down,-150*16,-60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,-135*16,-90*16);
            painter.drawArc(rectangle->up,-120*16,-120*16);
            break;
        }
        case 3:{
            painter.drawArc(rectangle->down,-30*16,60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,-45*16,90*16);
            painter.drawArc(rectangle->up,-60*16,120*16);
            break;
        }
        case 4:{
            painter.drawArc(rectangle->down,165*16,-60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,180*16,-90*16);
            painter.drawArc(rectangle->up,-165*16,-120*16);
            break;
        }
        case 5:{
            painter.drawArc(rectangle->down,15*16,60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,0,90*16);
            painter.drawArc(rectangle->up,-15*16,120*16);
            break;
        }
        case 6:{
            painter.drawArc(rectangle->down,-105*16,-60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,-90*16,-90*16);
            painter.drawArc(rectangle->up,-75*16,-120*16);
            break;
        }
        case 7:{
            painter.drawArc(rectangle->down,-15*16,-60*16);
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawArc(rectangle->mid,0,-90*16);
            painter.drawArc(rectangle->up,15*16,-120*16);
            break;
        }
        }
        break;
    }
    case 3:{
        pen.setColor(Qt::red);
        painter.setPen(pen);
        switch(direction){
        case 0:{
            painter.drawArc(rectangle->down,60*16,60*16);
            painter.drawArc(rectangle->mid,45*16,90*16);
            painter.drawArc(rectangle->up,30*16,120*16);
            break;
        }
        case 1:{
            painter.drawArc(rectangle->down,-60*16,-60*16);
            painter.drawArc(rectangle->mid,-45*16,-90*16);
            painter.drawArc(rectangle->up,-30*16,-120*16);
            break;
        }
        case 2:{
            painter.drawArc(rectangle->down,-150*16,-60*16);
            painter.drawArc(rectangle->mid,-135*16,-90*16);
            painter.drawArc(rectangle->up,-120*16,-120*16);
            break;
        }
        case 3:{
            painter.drawArc(rectangle->down,-30*16,60*16);
            painter.drawArc(rectangle->mid,-45*16,90*16);
            painter.drawArc(rectangle->up,-60*16,120*16);
            break;
        }
        case 4:{
            painter.drawArc(rectangle->down,165*16,-60*16);
            painter.drawArc(rectangle->mid,180*16,-90*16);
            painter.drawArc(rectangle->up,-165*16,-120*16);
            break;
        }
        case 5:{
            painter.drawArc(rectangle->down,15*16,60*16);
            painter.drawArc(rectangle->mid,0,90*16);
            painter.drawArc(rectangle->up,-15*16,120*16);
            break;
        }
        case 6:{
            painter.drawArc(rectangle->down,-105*16,-60*16);
            painter.drawArc(rectangle->mid,-90*16,-90*16);
            painter.drawArc(rectangle->up,-75*16,-120*16);
            break;
        }
        case 7:{
            painter.drawArc(rectangle->down,-15*16,-60*16);
            painter.drawArc(rectangle->mid,0,-90*16);
            painter.drawArc(rectangle->up,15*16,-120*16);
            break;
        }
        }
        break;
    }
    default: break;
    }
}

void Mycar::updateRadarTypeMap(QMap<int, int> &radarTypeMap){
    this->radarTypeMap=radarTypeMap; //更新雷达状态表
    update();
    return;
}

void Mycar::drawAllRadar(){
    if(!radarTypeMap.empty()&&!radarLocationMap.empty()){
        for(auto it=radarTypeMap.begin();it!=radarTypeMap.end();it++){
            int type=it.value();
            int direction;
            auto rect=radarLocationMap.find(it.key()); //找到超声波雷达绘制位置
            if(it.key()==0||it.key()==19) direction=0;
            else if(it.key()==9||it.key()==10) direction=1;
            else if(it.key()==2||it.key()==3||it.key()==4||it.key()==5||it.key()==6||it.key()==7) direction=2;
            else if(it.key()==12||it.key()==13||it.key()==14||it.key()==15||it.key()==16||it.key()==17) direction=3;
            else if(it.key()==1) direction=4;
            else if(it.key()==18) direction=5;
            else if(it.key()==8) direction=6;
            else if(it.key()==11) direction=7;
            if(rect!=radarLocationMap.end()){
                drawRadar(rect.value(),type,direction);
            }
            else{
                //弹出警告对话框，发生错误，无法找到超声波雷达位置
                QMessageBox::critical(this,"错误","绘制超声波雷达线时发生错误！/n"
                                                "（在索引表中没有找到雷达线绘制位置，请确认代码完整性，并保证在订阅雷达信息前完成索引表的构建！）");
                return;
            }
        }
    }
    else return;
}


void Mycar::getLocationMap(){
    std::shared_ptr<radarLocation> ptr[20];
    for(int i=0;i<20;i++) ptr[i]=std::make_shared<radarLocation>(); //动态申请20块内存空间存放超声波雷达位置
    QRectF up,mid,down;
    //下面从0——19号开始规定超声波雷达位置
    //No.0
    down=QRectF(QPointF(points_radar[0].x()-15,points_radar[0].y()-15),QPointF(points_radar[0].x()+15,points_radar[0].y()+15));
    mid=QRectF(QPointF(points_radar[0].x()-15,points_radar[0].y()-25),QPointF(points_radar[0].x()+15,points_radar[0].y()+5));
    up=QRectF(QPointF(points_radar[0].x()-20,points_radar[0].y()-35),QPointF(points_radar[0].x()+20,points_radar[0].y()-5));
    ptr[0]->down=down;
    ptr[0]->mid=mid;
    ptr[0]->up=up;
    radarLocationMap.insert(0,ptr[0]);
    //No.1
    down=QRectF(QPointF(points_radar[2].x()-15,points_radar[2].y()-15),QPointF(points_radar[2].x()+15,points_radar[2].y()+15));
    mid=QRectF(QPointF(points_radar[2].x()-22,points_radar[2].y()-22),QPointF(points_radar[2].x()+8,points_radar[2].y()+8));
    up=QRectF(QPointF(points_radar[2].x()-30,points_radar[2].y()-30),QPointF(points_radar[2].x()+7,points_radar[2].y()+7));
    ptr[1]->down=down;
    ptr[1]->mid=mid;
    ptr[1]->up=up;
    radarLocationMap.insert(1,ptr[1]);
    //No.2
    down=QRectF(QPointF(points_radar[4].x()-15,points_radar[4].y()+15),QPointF(points_radar[4].x()+15,points_radar[4].y()-15));
    mid=QRectF(QPointF(points_radar[4].x()-25,points_radar[4].y()+15),QPointF(points_radar[4].x()+5,points_radar[4].y()-15));
    up=QRectF(QPointF(points_radar[4].x()-35,points_radar[4].y()+20),QPointF(points_radar[4].x()-5,points_radar[4].y()-20));
    ptr[2]->down=down;
    ptr[2]->mid=mid;
    ptr[2]->up=up;
    radarLocationMap.insert(2,ptr[2]);
    //No.3
    down=QRectF(QPointF(points_radar[6].x()-15,points_radar[6].y()+15),QPointF(points_radar[6].x()+15,points_radar[6].y()-15));
    mid=QRectF(QPointF(points_radar[6].x()-25,points_radar[6].y()+15),QPointF(points_radar[6].x()+5,points_radar[6].y()-15));
    up=QRectF(QPointF(points_radar[6].x()-35,points_radar[6].y()+20),QPointF(points_radar[6].x()-5,points_radar[6].y()-20));
    ptr[3]->down=down;
    ptr[3]->mid=mid;
    ptr[3]->up=up;
    radarLocationMap.insert(3,ptr[3]);
    //No.4
    down=QRectF(QPointF(points_radar[8].x()-15,points_radar[8].y()+15),QPointF(points_radar[8].x()+15,points_radar[8].y()-15));
    mid=QRectF(QPointF(points_radar[8].x()-25,points_radar[8].y()+15),QPointF(points_radar[8].x()+5,points_radar[8].y()-15));
    up=QRectF(QPointF(points_radar[8].x()-35,points_radar[8].y()+20),QPointF(points_radar[8].x()-5,points_radar[8].y()-20));
    ptr[4]->down=down;
    ptr[4]->mid=mid;
    ptr[4]->up=up;
    radarLocationMap.insert(4,ptr[4]);
    //No.5
    down=QRectF(QPointF(points_radar[10].x()-15,points_radar[10].y()+15),QPointF(points_radar[10].x()+15,points_radar[10].y()-15));
    mid=QRectF(QPointF(points_radar[10].x()-25,points_radar[10].y()+15),QPointF(points_radar[10].x()+5,points_radar[10].y()-15));
    up=QRectF(QPointF(points_radar[10].x()-35,points_radar[10].y()+20),QPointF(points_radar[10].x()-5,points_radar[10].y()-20));
    ptr[5]->down=down;
    ptr[5]->mid=mid;
    ptr[5]->up=up;
    radarLocationMap.insert(5,ptr[5]);
    //No.6
    down=QRectF(QPointF(points_radar[12].x()-15,points_radar[12].y()+15),QPointF(points_radar[12].x()+15,points_radar[12].y()-15));
    mid=QRectF(QPointF(points_radar[12].x()-25,points_radar[12].y()+15),QPointF(points_radar[12].x()+5,points_radar[12].y()-15));
    up=QRectF(QPointF(points_radar[12].x()-35,points_radar[12].y()+20),QPointF(points_radar[12].x()-5,points_radar[12].y()-20));
    ptr[6]->down=down;
    ptr[6]->mid=mid;
    ptr[6]->up=up;
    radarLocationMap.insert(6,ptr[6]);
    //No.7
    down=QRectF(QPointF(points_radar[14].x()-15,points_radar[14].y()+15),QPointF(points_radar[14].x()+15,points_radar[14].y()-15));
    mid=QRectF(QPointF(points_radar[14].x()-25,points_radar[14].y()+15),QPointF(points_radar[14].x()+5,points_radar[14].y()-15));
    up=QRectF(QPointF(points_radar[14].x()-35,points_radar[14].y()+20),QPointF(points_radar[14].x()-5,points_radar[14].y()-20));
    ptr[7]->down=down;
    ptr[7]->mid=mid;
    ptr[7]->up=up;
    radarLocationMap.insert(7,ptr[7]);
    //No.8
    down=QRectF(points_radar[16].x()-15,points_radar[16].y()-15,30,30);
    mid=QRectF(points_radar[16].x()-22,points_radar[16].y()-8,30,30);
    up=QRectF(points_radar[16].x()-29-3,points_radar[16].y()-1-6,40,40);
    ptr[8]->down=down;
    ptr[8]->mid=mid;
    ptr[8]->up=up;
    radarLocationMap.insert(8,ptr[8]);
    //No.9
    down=QRectF(QPointF(points_radar[18].x()+15,points_radar[18].y()+15),QPointF(points_radar[18].x()-15,points_radar[18].y()-15));
    mid=QRectF(QPointF(points_radar[18].x()+15,points_radar[18].y()+25),QPointF(points_radar[18].x()-15,points_radar[18].y()-5));
    up=QRectF(QPointF(points_radar[18].x()+20,points_radar[18].y()+35),QPointF(points_radar[18].x()-20,points_radar[18].y()+5));
    ptr[9]->down=down;
    ptr[9]->mid=mid;
    ptr[9]->up=up;
    radarLocationMap.insert(9,ptr[9]);
    //No.10
    down=QRectF(QPointF(points_radar[19].x()+15,points_radar[19].y()+15),QPointF(points_radar[19].x()-15,points_radar[19].y()-15));
    mid=QRectF(QPointF(points_radar[19].x()+15,points_radar[19].y()+25),QPointF(points_radar[19].x()-15,points_radar[19].y()-5));
    up=QRectF(QPointF(points_radar[19].x()+20,points_radar[19].y()+35),QPointF(points_radar[19].x()-20,points_radar[19].y()+5));
    ptr[10]->down=down;
    ptr[10]->mid=mid;
    ptr[10]->up=up;
    radarLocationMap.insert(10,ptr[10]);
    //No.11
    down=QRectF(QPointF(points_radar[17].x()-15,points_radar[17].y()-15),QPointF(points_radar[17].x()+15,points_radar[17].y()+15));
    mid=QRectF(QPointF(points_radar[17].x()-8,points_radar[17].y()-8),QPointF(points_radar[17].x()+22,points_radar[17].y()+22));
    up=QRectF(QPointF(points_radar[17].x()-7,points_radar[17].y()-7),QPointF(points_radar[17].x()+30,points_radar[17].y()+30));
    ptr[11]->down=down;
    ptr[11]->mid=mid;
    ptr[11]->up=up;
    radarLocationMap.insert(11,ptr[11]);
    //No.12
    down=QRectF(QPointF(points_radar[15].x()+15,points_radar[15].y()-15),QPointF(points_radar[15].x()-15,points_radar[15].y()+15));
    mid=QRectF(QPointF(points_radar[15].x()+25,points_radar[15].y()-15),QPointF(points_radar[15].x()-5,points_radar[15].y()+15));
    up=QRectF(QPointF(points_radar[15].x()+35,points_radar[15].y()-20),QPointF(points_radar[15].x()+5,points_radar[15].y()+20));
    ptr[12]->down=down;
    ptr[12]->mid=mid;
    ptr[12]->up=up;
    radarLocationMap.insert(12,ptr[12]);
    //No.13
    down=QRectF(QPointF(points_radar[13].x()+15,points_radar[13].y()-15),QPointF(points_radar[13].x()-15,points_radar[13].y()+15));
    mid=QRectF(QPointF(points_radar[13].x()+25,points_radar[13].y()-15),QPointF(points_radar[13].x()-5,points_radar[13].y()+15));
    up=QRectF(QPointF(points_radar[13].x()+35,points_radar[13].y()-20),QPointF(points_radar[13].x()+5,points_radar[13].y()+20));
    ptr[13]->down=down;
    ptr[13]->mid=mid;
    ptr[13]->up=up;
    radarLocationMap.insert(13,ptr[13]);
    //No.14
    down=QRectF(QPointF(points_radar[11].x()+15,points_radar[11].y()-15),QPointF(points_radar[11].x()-15,points_radar[11].y()+15));
    mid=QRectF(QPointF(points_radar[11].x()+25,points_radar[11].y()-15),QPointF(points_radar[11].x()-5,points_radar[11].y()+15));
    up=QRectF(QPointF(points_radar[11].x()+35,points_radar[11].y()-20),QPointF(points_radar[11].x()+5,points_radar[11].y()+20));
    ptr[14]->down=down;
    ptr[14]->mid=mid;
    ptr[14]->up=up;
    radarLocationMap.insert(14,ptr[14]);
    //No.15
    down=QRectF(QPointF(points_radar[9].x()+15,points_radar[9].y()-15),QPointF(points_radar[9].x()-15,points_radar[9].y()+15));
    mid=QRectF(QPointF(points_radar[9].x()+25,points_radar[9].y()-15),QPointF(points_radar[9].x()-5,points_radar[9].y()+15));
    up=QRectF(QPointF(points_radar[9].x()+35,points_radar[9].y()-20),QPointF(points_radar[9].x()+5,points_radar[9].y()+20));
    ptr[15]->down=down;
    ptr[15]->mid=mid;
    ptr[15]->up=up;
    radarLocationMap.insert(15,ptr[15]);
    //No.16
    down=QRectF(QPointF(points_radar[7].x()+15,points_radar[7].y()-15),QPointF(points_radar[7].x()-15,points_radar[7].y()+15));
    mid=QRectF(QPointF(points_radar[7].x()+25,points_radar[7].y()-15),QPointF(points_radar[7].x()-5,points_radar[7].y()+15));
    up=QRectF(QPointF(points_radar[7].x()+35,points_radar[7].y()-20),QPointF(points_radar[7].x()+5,points_radar[7].y()+20));
    ptr[16]->down=down;
    ptr[16]->mid=mid;
    ptr[16]->up=up;
    radarLocationMap.insert(16,ptr[16]);
    //No.17
    down=QRectF(QPointF(points_radar[5].x()+15,points_radar[5].y()-15),QPointF(points_radar[5].x()-15,points_radar[5].y()+15));
    mid=QRectF(QPointF(points_radar[5].x()+25,points_radar[5].y()-15),QPointF(points_radar[5].x()-5,points_radar[5].y()+15));
    up=QRectF(QPointF(points_radar[5].x()+35,points_radar[5].y()-20),QPointF(points_radar[5].x()+5,points_radar[5].y()+20));
    ptr[17]->down=down;
    ptr[17]->mid=mid;
    ptr[17]->up=up;
    radarLocationMap.insert(17,ptr[17]);
    //No.18
    down=QRectF(points_radar[3].x()-15,points_radar[3].y()-15,30,30);
    mid=QRectF(points_radar[3].x()-8,points_radar[3].y()-22,30,30);
    up=QRectF(points_radar[3].x()-1-8,points_radar[3].y()-29-3,40,40);
    ptr[18]->down=down;
    ptr[18]->mid=mid;
    ptr[18]->up=up;
    radarLocationMap.insert(18,ptr[18]);
    //No.19
    down=QRectF(QPointF(points_radar[1].x()-15,points_radar[1].y()-15),QPointF(points_radar[1].x()+15,points_radar[1].y()+15));
    mid=QRectF(QPointF(points_radar[1].x()-15,points_radar[1].y()-25),QPointF(points_radar[1].x()+15,points_radar[1].y()+5));
    up=QRectF(QPointF(points_radar[1].x()-20,points_radar[1].y()-35),QPointF(points_radar[1].x()+20,points_radar[1].y()-5));
    ptr[19]->down=down;
    ptr[19]->mid=mid;
    ptr[19]->up=up;
    radarLocationMap.insert(19,ptr[19]);
}

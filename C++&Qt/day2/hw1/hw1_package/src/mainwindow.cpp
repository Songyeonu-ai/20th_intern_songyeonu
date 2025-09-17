#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Timer1 = new QTimer(this);
    Timer2 = new QTimer(this);
    Timer3 = new QTimer(this);
    Timer1->setInterval(100);
    Timer2->setInterval(100);
    Timer3->setInterval(100);

    connect(Timer1, &QTimer::timeout, this, &MainWindow::rotate1);
    connect(Timer2, &QTimer::timeout, this, &MainWindow::rotate2);
    connect(Timer3, &QTimer::timeout, this, &MainWindow::rotate3);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen1(Qt::black, 10);
        painter.setPen(pen1);
        painter.translate(260, 320);        //화면 중간쯤
        painter.rotate(joint_degree[0]);       // 관절 1 회전
        painter.drawLine(0, 0, 100, 0);     //팔 그리기

        // 2번째 관절
        QPen pen2(Qt::red, 7);
        painter.setPen(pen2);
        painter.translate(100, 0);          // 첫 번째 팔 끝
        painter.rotate(joint_degree[1]);       // 관절 2 회전
        painter.drawLine(0, 0, 80, 0);

        QPen pen3(Qt::blue, 4);
        painter.setPen(pen3);
        painter.translate(80, 0);
        painter.rotate(joint_degree[2]);
        painter.drawLine(0, 0, 50, 0);

        QPen pen4(Qt::green, 4); //그리퍼 부분 표시
        painter.setPen(pen4);
        painter.translate(50,0);

        painter.drawLine(0, 10, 0, 0);
        painter.translate(0, 10);
        painter.drawLine(0, 0, 7, 0);
        painter.translate(0, -15);

        painter.drawLine(0, 0, 0, 10);
        painter.translate(0, -5);
        painter.drawLine(0, 0, 7, 0);

}

void MainWindow::rotateJoint_CW(int joint_degree)
{
    joint_degree += 5;             // 각도 증가
    if (joint_degree >= 356) joint_degree = 0;
    repaint();
}

void MainWindow::rotateJoint_CCW(int joint_degree)
{
    joint_degree -= 5;             // 각도 감소
    if (joint_degree <= 0) joint_degree = 356;
    repaint();
}
void MainWindow::on_dial_valueChanged(int value)
{
    cout<<"Joint 1 moved: "<<value<<endl;
    joint_degree[0]=value*4;
    repaint();
}


void MainWindow::on_dial_3_valueChanged(int value)
{
    cout<<"Joint 3 moved: "<<value<<endl;
    joint_degree[2]=value*4;
    repaint();
}


void MainWindow::on_dial_2_valueChanged(int value)
{
    cout<<"Joint 2 moved: "<<value<<endl;
    joint_degree[1]=value*4;
    repaint();
}


void MainWindow::on_pushButton_7_clicked()
{
    //txt load
    ifstream load;

    load.open("mani_save.txt");

    load>>joint_degree[0];
    load>>joint_degree[1];
    load>>joint_degree[2];
   load.close();
   repaint();
}

void MainWindow::on_pushButton_8_clicked()
{
    //txt save
    ofstream save;

    save.open("mani_save.txt");

    save<<joint_degree[0]<<"\n";
    save<<joint_degree[1]<<"\n";
    save<<joint_degree[2]<<"\n";
   save<<endl;
   save.close();
}

void MainWindow::on_pushButton_clicked()
{
   if(Timer1->isActive() && rotDirec[0] ==1){
       Timer1->stop();
       rotDirec[0]=0;
   }else {
       rotDirec[0]=1;
       if(!Timer1->isActive())Timer1->start();
   }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(Timer1->isActive() && rotDirec[0] ==-1){
        Timer1->stop();
        rotDirec[0]=0;
    }else {
        rotDirec[0]=-1;
        if(!Timer1->isActive())Timer1->start();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(Timer2->isActive() && rotDirec[1] ==1){
        Timer2->stop();
        rotDirec[1]=0;
    }else {
        rotDirec[1]=1;
        if(!Timer2->isActive())Timer2->start();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(Timer2->isActive() && rotDirec[1] ==-1){
        Timer2->stop();
        rotDirec[1]=0;
    }else {
        rotDirec[1]=-1;
        if(!Timer2->isActive())Timer2->start();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if(Timer3->isActive() && rotDirec[2] ==1){
        Timer3->stop();
        rotDirec[2]=0;
    }else {
        rotDirec[2]=1;
        if(!Timer3->isActive())Timer3->start();
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(Timer3->isActive() && rotDirec[2] ==-1){
        Timer3->stop();
        rotDirec[2]=0;
    }else {
        rotDirec[2]=-1;
        if(!Timer3->isActive())Timer3->start();
    }
}

void MainWindow::rotate1(){
    joint_degree[0] = (joint_degree[0] + rotDirec[0]*5 + 360) % 360;
    repaint();
}
void MainWindow::rotate2(){
    joint_degree[1] = (joint_degree[1] + rotDirec[1]*5 + 360) % 360;
    repaint();
}
void MainWindow::rotate3(){
    joint_degree[2] = (joint_degree[2] + rotDirec[2]*5 + 360) % 360;
    repaint();
}





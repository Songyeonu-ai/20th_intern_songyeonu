/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/hw4/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
  // connect(qnode, &QNode::receivedMessage, this, [this](QString msg){
  //   ui->label_2->setText(msg);
  // });
  qnode->start();
  Timer1 = new QTimer(this);
  Timer2 = new QTimer(this);
  Timer1->setInterval(100);
  Timer2->setInterval(100);
  connect(qnode, &QNode::receivedMessage_CW, this, [this]() {
    Timer1->start();
  });
  connect(qnode, &QNode::receivedMessage_CCW, this, [this]() {
    Timer2->start();
  });
  connect(Timer1, &QTimer::timeout, this, &MainWindow::rotateJoint_CW);
  connect(Timer2, &QTimer::timeout, this, &MainWindow::rotateJoint_CCW);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
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
        painter.rotate(joint_degree);       // 관절 1 회전
        painter.drawLine(0, 0, 100, 0);     //팔 그리기

        // 2번째 관절
        QPen pen2(Qt::red, 7);
        painter.setPen(pen2);
        painter.translate(100, 0);          // 첫 번째 팔 끝
        painter.rotate(joint_degree);       // 관절 2 회전
        painter.drawLine(0, 0, 80, 0);

        QPen pen3(Qt::blue, 4);
        painter.setPen(pen3);
        painter.translate(80, 0);
        painter.rotate(joint_degree);
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

void MainWindow::rotateJoint_CW()
{
    joint_degree += 5;             // 각도 증가
    if (joint_degree >= 356) joint_degree = 0;
    repaint();
}

void MainWindow::rotateJoint_CCW()
{
    joint_degree -= 5;             // 각도 감소
    if (joint_degree <= 0) joint_degree = 356;
    repaint();
}

// void MainWindow::rotate1(){
//     joint_degree[0] = (joint_degree[0] + rotDirec[0]*5 + 360) % 360;
//     repaint();
// }
// void MainWindow::rotate2(){
//     joint_degree[1] = (joint_degree[1] + rotDirec[1]*5 + 360) % 360;
//     repaint();
// }
// void MainWindow::rotate3(){
//     joint_degree[2] = (joint_degree[2] + rotDirec[2]*5 + 360) % 360;
//     repaint();
// }

void MainWindow::on_pushButton_clicked()
{
    
    QString text = ui->textEdit->toPlainText();
    // qnode->setMessage(text);
    qnode->publishing(text);
    ui->label->setText(text);

}

void MainWindow::on_pushButton_2_clicked()
{
    Timer1->stop();
    Timer2->stop();
    ui->label_2->setText("STOP");
}





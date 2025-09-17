/**
 * @file /include/% (package)s/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef hw4_MAIN_WINDOW_H
#define hw4_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"
#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <rclcpp/rclcpp.hpp>

using namespace std;

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  Ui::MainWindowDesign* ui;
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;
  void label_2(QString *msg);
  void paintEvent(QPaintEvent *e);
  void onBtnPress();
  void rotateJoint_CW();
  void rotateJoint_CCW();
  void rotate1();
  void rotate2();
  void rotate3();
private slots:
  void on_pushButton_clicked();
  
  void on_pushButton_2_clicked();
  

private:
  std::shared_ptr<rclcpp::Node> node_;
  void closeEvent(QCloseEvent* event);
  int link_1, link_2, link_3;
  int joint1_angle = 0;
  int _degree =0;
  int joint_degree;//회전각
  int rotDirec[3]={0};
  QTimer *Timer1;
  QTimer *Timer2;
};

#endif  // % (package)s_MAIN_WINDOW_H

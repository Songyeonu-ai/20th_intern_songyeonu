/**
 * @file /include/% (package)s/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef test3_MAIN_WINDOW_H
#define test3_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

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

private slots:
  void on_pushButton_clicked();
  
  void on_pushButton_2_clicked();

private:
  void closeEvent(QCloseEvent* event);
};

#endif  // % (package)s_MAIN_WINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QTimer>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void onBtnPress();
    void rotateJoint_CW(int joint_degree);
    void rotateJoint_CCW(int joint_degree);
    void rotate1();
    void rotate2();
    void rotate3();

private slots:

    void on_dial_valueChanged(int value);

    void on_dial_3_valueChanged(int value);

    void on_dial_2_valueChanged(int value);


    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *Timer1;
    QTimer *Timer2;
    QTimer *Timer3;
    int joint1_angle = 0;
    int _degree =0;
    int joint_degree[3]={0};//회전각
    int rotDirec[3]={0};

};



#endif // MAINWINDOW_H

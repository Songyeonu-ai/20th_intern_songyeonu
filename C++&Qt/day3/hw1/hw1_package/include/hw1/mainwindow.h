#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <fstream>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Put_text_3(int timernum, const char *num1, const char *num2, const char *num3);
    void Put_text_4(int timernum, const char *num1, const char *num2, const char *num3, const char *num4);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_16_released();
    void on_pushButton_16_pressed();
    void on_pushButton_released();
    void on_pushButton_pressed();
    void on_pushButton_2_released();
    void on_pushButton_2_pressed();
    void on_pushButton_3_released();
    void on_pushButton_3_pressed();
    void on_pushButton_4_released();
    void on_pushButton_4_pressed();
    void on_pushButton_5_released();
    void on_pushButton_5_pressed();
    void on_pushButton_6_released();
    void on_pushButton_6_pressed();
    void on_pushButton_7_released();
    void on_pushButton_7_pressed();
    void on_pushButton_8_released();
    void on_pushButton_8_pressed();
    void on_pushButton_9_released();
    void on_pushButton_9_pressed();
    void on_pushButton_10_released();
    void on_pushButton_10_pressed();
    void on_pushButton_15_released();
    void on_pushButton_15_pressed();
    void on_pushButton_18_released();
    void on_pushButton_18_pressed();
    void on_pushButton_17_released();
    void on_pushButton_17_pressed();
    void on_pushButton_14_pressed();
    void on_pushButton_14_released();

private:
    Ui::MainWindow *ui;
    int count[10];
    QElapsedTimer *timer[10];
    bool isLargeMode;
    bool isclicked;
};
#endif // MAINWINDOW_H

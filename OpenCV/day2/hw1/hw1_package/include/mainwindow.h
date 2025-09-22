#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <QTimer>

const std::string window_detection_name = "Object Detection";


using namespace cv;
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
    void streaming();
    void make_binary();
    void make_box();
    

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_6_sliderMoved(int position);

    void on_horizontalSlider_5_sliderMoved(int position);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //출력한 프레임 수를 저장할 변수 선언 및 초기화
    int frame_cnt = 0;
    Mat bus_img, white, blue, neon, orange, white_b, blue_b, neon_b, orange_b, img;
    Mat src, label, stats, centroids, src_color ;
    int whatclk;
    bool is_play;
    QTimer *timer;
    QTimer *timer_box;
    QTimer *timer_range;
    int hsv[24]={0};
    bool ranging;
    int x[4];
    int y[4];
    int width[4];
    int height[4];
    VideoCapture cap;
};

#endif // MAINWINDOW_H

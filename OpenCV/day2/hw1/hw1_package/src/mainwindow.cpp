#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>


using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if(!cap.open(1)) {
        qDebug() << "Could not open camera";
        return;
    }

    ui->setupUi(this);
    cap >> bus_img;

    if (!cap.isOpened())
    {
        std::cout << "Could not open video" << 0 << std::endl;
    }
    whatclk =0;
    is_play = true;
    ranging = true;
    int max_value_H=0; int max_value_S=0; int max_value_V=0;
    timer = new QTimer(this);
    timer_box = new QTimer(this);
    timer_range = new QTimer(this);

    timer->setInterval(100);
    timer_box->setInterval(100);
    timer_range->setInterval(100);
    connect(timer, &QTimer::timeout, this, &MainWindow::streaming);
    // connect(timer_box, &QTimer::timeout, this, &MainWindow::make_box);
    connect(timer_range, &QTimer::timeout, this, &MainWindow::make_binary);
    timer->start();
    timer_box->start();
    timer_range->start();
}

void MainWindow::streaming(){
    if(is_play){
        cap >> bus_img;
        if(bus_img.empty())
        {
            std::cout << "video end" << std::endl;
            return;
        }

        cvtColor(bus_img, img, COLOR_BGR2HSV);
        
        {inRange(img, Scalar(hsv[12], hsv[16], hsv[20]), Scalar(hsv[0], hsv[4], hsv[8]), white);qDebug() << whatclk;imshow("ddd", white);}
        {inRange(img, Scalar(hsv[13], hsv[17], hsv[21]), Scalar(hsv[1], hsv[5], hsv[9]), blue);qDebug() << whatclk;}
        {inRange(img, Scalar(hsv[14], hsv[18], hsv[22]), Scalar(hsv[2], hsv[6], hsv[10]), neon);qDebug() << whatclk;}
        {inRange(img, Scalar(hsv[15], hsv[19], hsv[23]), Scalar(hsv[3], hsv[7], hsv[11]), orange);qDebug() << whatclk;}
        
        cvtColor(bus_img, src, COLOR_RGB2GRAY );
        int num = connectedComponentsWithStats(src, label, stats, centroids, 8, CV_32S);
        cvtColor(src, src_color, COLOR_GRAY2BGR);
        RNG rng(12345);
        for (int i = 1; i < num; ++i) {
            x[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_LEFT));
            y[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_TOP));
            width[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_WIDTH));
            height[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_HEIGHT));
            qDebug()<<"making box..."<<i<<"\n";

        rectangle(src_color, Rect(x[i-1], y[i-1], width[i-1], height[i-1]), Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)));
        }
        // white_b= img(Range(y[0]-height[0], y[0]), Range(x[0], x[0]+width[0]));
        // blue_b= img(Range(y[1]-height[1], y[1]), Range(x[1], x[1]+width[1]));
        // neon_b= img(Range(y[2]-height[2], y[2]), Range(x[2], x[2]+width[2]));
        // orange_b= img(Range(y[3]-height[3], y[3]), Range(x[3], x[3]+width[3]));
        ui->label_6->setPixmap(QPixmap::fromImage(QImage(src_color.data, src_color.cols, src_color.rows, src_color.step, QImage::Format_BGR888)));

         QImage qimg(neon.data, neon.cols, neon.rows, neon.step, QImage::Format_Grayscale8);
         ui->label_2->setPixmap(QPixmap::fromImage(qimg).scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        
         QImage qimg_2(orange.data, orange.cols, orange.rows, orange.step, QImage::Format_Grayscale8);
         ui->label_3->setPixmap(QPixmap::fromImage(qimg_2).scaled(ui->label_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

         QImage qimg_3(blue.data, blue.cols, blue.rows, blue.step, QImage::Format_Grayscale8);
         ui->label_4->setPixmap(QPixmap::fromImage(qimg_3).scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

         QImage qimg_4(white.data, white.cols, white.rows, white.step, QImage::Format_Grayscale8);
         ui->label_5->setPixmap(QPixmap::fromImage(qimg_4).scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->label->setPixmap(QPixmap::fromImage(QImage(bus_img.data, bus_img.cols, bus_img.rows, bus_img.step, QImage::Format_BGR888)));

        // ui->label_7->setPixmap(QPixmap::fromImage(QImage(neon_b.data, neon_b.cols, neon_b.rows, neon_b.step, QImage::Format_BGR888)));
        // ui->label_8->setPixmap(QPixmap::fromImage(QImage(orange_b.data, orange_b.cols, orange_b.rows, orange_b.step, QImage::Format_BGR888)));
        // ui->label_9->setPixmap(QPixmap::fromImage(QImage(blue_b.data, blue_b.cols, blue_b.rows, blue_b.step, QImage::Format_BGR888)));
        // ui->label_10->setPixmap(QPixmap::fromImage(QImage(white_b.data, white_b.cols, white_b.rows, white_b.step, QImage::Format_BGR888)));

        qDebug() << "스트리밍 실행 중";
    }
}

void MainWindow::make_binary(){ //inranging
    
}

// void MainWindow::make_box(){
    
//     cvtColor(bus_img, src, COLOR_RGB2GRAY );
//     int num = connectedComponentsWithStats(src, label, stats, centroids, 8, CV_32S);
//     cvtColor(src, src_color, COLOR_GRAY2BGR);
//     RNG rng(12345);
//     for (int i = 1; i < num; ++i) {
//         x[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_LEFT));
//         y[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_TOP));
//         width[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_WIDTH));
//         height[i-1] = static_cast<int>(stats.at<int>(i, CC_STAT_HEIGHT));

//     rectangle(src_color, Rect(x[i-1], y[i-1], width[i-1], height[i-1]), Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)));
//     }
//     white_b= img(Range(y[0], y[0]-height[0]), Range(x[0], x[0]+width[0]));
//     blue_b= img(Range(y[1], y[1]-height[1]), Range(x[1], x[1]+width[1]));
//     neon_b= img(Range(y[2], y[2]-height[2]), Range(x[2], x[2]+width[2]));
//     orange_b= img(Range(y[3], y[3]-height[3]), Range(x[3], x[3]+width[3]));
//     ui->label_6->setPixmap(QPixmap::fromImage(QImage(src_color.data, src_color.cols, src_color.rows, src_color.step, QImage::Format_BGR888)));
// }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked() //white
{
    whatclk =1;
}


void MainWindow::on_radioButton_2_clicked() //blue
{
    whatclk =2;
}


void MainWindow::on_radioButton_3_clicked() //neon
{
    whatclk =3;
}


void MainWindow::on_radioButton_4_clicked() //orange
{
    whatclk =4;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position) //hue high
{
    if(whatclk==0)return;
    hsv[whatclk-1]=position;
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position) //hue low
{
    if(whatclk==0)return;
    hsv[whatclk+11]=position;
}


void MainWindow::on_horizontalSlider_4_sliderMoved(int position) //sat high
{
    if(whatclk==0)return;
    hsv[3+whatclk]=position;
}


void MainWindow::on_horizontalSlider_3_sliderMoved(int position) //sat low
{
    if(whatclk==0)return;
    hsv[15+whatclk]=position;
}


void MainWindow::on_horizontalSlider_6_sliderMoved(int position) //val high
{
    if(whatclk==0)return;
    hsv[7+whatclk]=position;
}


void MainWindow::on_horizontalSlider_5_sliderMoved(int position) //val low
{
    if(whatclk==0)return;
    hsv[19+whatclk]=position;
}


void MainWindow::on_pushButton_clicked()
{
    ranging = !ranging;
}

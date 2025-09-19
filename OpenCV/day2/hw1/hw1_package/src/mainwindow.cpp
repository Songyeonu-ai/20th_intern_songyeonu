#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUdpSocket>
#include <QDebug>
#include <QTime>
#include <QDate>


using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    VideoCapture cap(0);
    ui->setupUi(this);
    cap >> bus_img;
    //video_path로 부터 파일 정보를 가져오지 못할 경우
    if (!cap.isOpened())
    {
        std::cout << "Could not open video" << 0 << std::endl;
    }
    whatclk =0;
    int hsv[12]={0};
    is_play = true;
    ranging = true;
    int low_H = 0, low_S = 0, low_V = 0;
    low_H = hsv[whatclk+11]; low_S = hsv[whatclk+15]; low_V=[whatclk+19];
    int max_value_H=0; int max_value_S=0; int max_value_V=0;
    int high_H = hsv[whatclk-1]; int high_S = hsv[whatclk+3]; int high_V = hsv[whatclk+7];
    high_H = max_value_H; high_S = max_value; high_V = max_value;
    
    timer = new QTimer(this);
    timer_box = new QTimer(this);
    
    timer->setInterval(100);
    timer_box->setInterval(100);
    timer_range->setInterval(100);

    connect(timer, &QTimer::timeout, this, &MainWindow::streaming);
    connect(timer_box, &QTimer::timeout, this, &MainWindow::make_box);
    connect(timer_range, &QTimer::timeout, this, &MainWindow::make_binary);
}
static void on_low_H_thresh_trackbar(int, void *)
{
    hsv[11+whatclk] = min(hsv[whatclk-1]-1, hsv[11+whatclk]);
    setTrackbarPos("Low H", window_detection_name, hsv[11+whatclk]);
}
 
static void on_high_H_thresh_trackbar(int, void *)
{
    hsv[whatclk-1]= max(hsv[whatclk-1], hsv[11+whatclk]+1);
    setTrackbarPos("High H", window_detection_name, hsv[whatclk-1]);
}
 
static void on_low_S_thresh_trackbar(int, void *)
{
    hsv[15+whatclk] = min(hsv[whatclk+3]-1, hsv[15+whatclk]);
    setTrackbarPos("Low S", window_detection_name, hsv[15+whatclk]);
}
 
static void on_high_S_thresh_trackbar(int, void *)
{
    hsv[whatclk+3] = max(hsv[whatclk+3], hsv[15+whatclk]+1);
    setTrackbarPos("High S", window_detection_name, hsv[whatclk+3]);
}
 
static void on_low_V_thresh_trackbar(int, void *)
{
    hsv[19+whatclk] = min(hsv[whatclk+7]-1, hsv[19+whatclk]);
    setTrackbarPos("Low V", window_detection_name, hsv[19+whatclk]);
}
 
static void on_high_V_thresh_trackbar(int, void *)
{
    hsv[whatclk+7] = max(hsv[whatclk+7], hsv[19+whatclk]+1);
    setTrackbarPos("High V", window_detection_name, hsv[whatclk+7]);
}

void MainWindow::streaming(){
    //bus_video로부터 하나의 프레임을 읽어 bus_img에 저장
    if(is_play){
        VideoCapture cap(0);
        cap >> bus_img;
        //bus_img가 전달받은 이미지가 없다면
        if(bus_img.empty())
        {
            std::cout << "video end" << std::endl;
            return;
        }

        //opencv로 받아온 이미지는 BGR 형태로 저장되므로 마지막 플래그를 BFR888로 전달하여 이미지 저장
        ui->label->setPixmap(QPixmap::fromImage(QImage(bus_img.data, bus_img.cols, bus_img.rows, bus_img.step, QImage::Format_BGR888)));
        ui->label_2->setPixmap(QPixmap::fromImage(QImage(neon.data, neon.cols, neon.rows, neon.step, QImage::Format_BGR888)));
        ui->label_3->setPixmap(QPixmap::fromImage(QImage(orange.data, orange.cols, orange.rows, orange.step, QImage::Format_BGR888)));
        ui->label_4->setPixmap(QPixmap::fromImage(QImage(blue.data, blue.cols, blue.rows, blue.step, QImage::Format_BGR888)));
        ui->label_5->setPixmap(QPixmap::fromImage(QImage(white.data, white.cols, white.rows, white.step, QImage::Format_BGR888)));
        //비디오 프레임 카운트 변수, 생략해도 상관없다
        //frame_cnt++;
        char c = (char)waitKey(0);
    }
}

void MainWindow::make_binary(){ //inranging
    if(ranging){
         if(bus_img.empty())
        {
            break;
        }
        cvtColor(bus_img, img, COLOR_BGR2HSV);
        switch(whatclk){
            case 1: {inRange(img, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), white);}break;
            case 2: {inRange(img, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), blue);}break;
            case 3: {inRange(img, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), neon);}break;
            case 4: {inRange(img, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), orange);}break;
            default:break;
        }
    }
}
void MainWindow::setting_hsv(){ //슬롯 값 읽어오기
    createTrackbar("Low H", window_detection_name, hsv[11+whatclk], max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, hsv[whatclk-1], max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, hsv[15+whatclk], max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, hsv[whatclk+3], max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, hsv[19+whatclk], max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, hsv[whatclk+7], max_value, on_high_V_thresh_trackbar);
}
void MainWindow::make_box(){
    Mat src;
    cvtColor(bus_img, src, COLOR_RGB2GRAY );
    Mat label, stats, centroids;
    int num = connectedComponentsWithStats(src, label, stats, centroids, 8, CV_32S);
    Mat src_color;
    cvtColor(src, src_color, COLOR_GRAY2BGR);

    RNG rng(12345);

    for (int i = 1; i < num; ++i) {
        int x = static_cast<int>(stats.at<int>(i, CC_STAT_LEFT));
        int y = static_cast<int>(stats.at<int>(i, CC_STAT_TOP));
        int width = static_cast<int>(stats.at<int>(i, CC_STAT_WIDTH));
        int height = static_cast<int>(stats.at<int>(i, CC_STAT_HEIGHT));

        rectangle(src_color, Rect(x, y, width, height), Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)));
        }
        ui->label_6->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


int strlenn(const char *str){ //문자열 길이 구하기
    int count=0;
    while(*str){
        count++;
        str++;
    }
    return count;
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
    setting_hsv();
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position) //hue low
{
    if(whatclk==0)return;
    hsv[whatclk+11]=position;
    setting_hsv();
}


void MainWindow::on_horizontalSlider_4_sliderMoved(int position) //sat high
{
    if(whatclk==0)return;
    hsv[3+whatclk]=position;
    setting_hsv();
}


void MainWindow::on_horizontalSlider_3_sliderMoved(int position) //sat low
{
    if(whatclk==0)return;
    hsv[15+whatclk]=position;
    setting_hsv();
}


void MainWindow::on_horizontalSlider_6_sliderMoved(int position) //val high
{
    if(whatclk==0)return;
    hsv[7+whatclk]=position;
    setting_hsv();
}


void MainWindow::on_horizontalSlider_5_sliderMoved(int position) //val low
{
    if(whatclk==0)return;
    hsv[19+whatclk]=position;
    setting_hsv();
}


void MainWindow::on_pushButton_clicked()
{
    ranging != ranging;
}

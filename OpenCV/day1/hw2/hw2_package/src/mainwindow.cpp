#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUdpSocket>
#include <QDebug>
#include <QTime>
#include <QDate>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //소켓 선언
    udpSocket = new QUdpSocket(this);
    //소켓 바인드
    udpSocket->bind(QHostAddress::AnyIPv4, 9999, QUdpSocket::ShareAddress);
    //커넥트(들어오면 읽기)
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readDatagram);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readDatagram()
{
    while (udpSocket->hasPendingDatagrams()) {

        Mat img;
        std::vector<char> buf;

        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;  //받은 아이피
        quint16 senderPort; //포트

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        qDebug() << "Received from" << sender.toString()//Qstring형태 문자열을 바로 보낼 수 있도록 qDebug 사용
                 << ":" << senderPort
                 << "->" << datagram; //터미널에 표시

        img = cv::imdecode(cv::Mat(1, datagram.size(), CV_8UC1, datagram.data()), cv::IMREAD_UNCHANGED);
        cv::imshow( "Server", img );
        cv::waitKey(0);
    }
}

int strlenn(const char *str){ //문자열 길이 구하기
    int count=0;
    while(*str){
        count++;
        str++;
    }
    return count;
}


void MainWindow::on_pushButton_clicked()
{

    //VideoCapture cap(0);
    Mat img = cv::imread("/home/yu/intern_ws/OpenCV/hw2/homework1.jpg");
    //cap >> img;

    if(img.empty()){
        return;
    }

    cv::resize(img, img, Size(640, 480));

    std::vector<uchar> buf;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(50); // compression quality, ranges between 0-100

    if (!cv::imencode(".jpg", img, buf, params)) {
        std::cout << "JPEG compression failed.\n";
    }

    const char* c = (const char*)buf.data(); //문자열 변환
    if(strlenn(c)>0){
        QByteArray datagram = QByteArray(c); //다시 변환
    udpSocket->writeDatagram(datagram, QHostAddress("192.168.0.49"), 9999);
    }
}




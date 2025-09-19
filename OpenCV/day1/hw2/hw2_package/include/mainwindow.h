#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

#include <opencv2/opencv.hpp>

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
    void istextExist();

private slots:
    void readDatagram();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
};

int strlenn(const char *str);

#endif // MAINWINDOW_H

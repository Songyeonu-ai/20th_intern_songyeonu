#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <vector>
using namespace std;

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Push(int money);
    void Pop(int money, int &Pop_index);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    vector<int> bank_account;
    int money;
    int Push_index;
    int Pop_index;
};
#endif // MAINWINDOW_H

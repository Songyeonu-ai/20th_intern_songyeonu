#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));
    Push_index=0;
    Pop_index=0;
    money=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Push(int money){
    bank_account.push_back(money);
    cout<<"계좌 "<<Push_index<<"입금 내역:"<<money<<endl;
    Push_index++;
}

void MainWindow::Pop(int money, int &Pop_index){
    if(Push_index >= 0 && Pop_index <bank_account.size()){
        if(bank_account.at(Pop_index)>=money){
            cout<<Pop_index<<"-인출: "<<money<<endl;
            bank_account.at(Pop_index)-=money;
            Pop_index++;
        }else{
            cout<<"잔고 부족-잔고"<<':'<<bank_account[Pop_index]<<endl;
        }
    }else{
        cout<<"Wrong Access!"<<endl;
    }
}


void MainWindow::on_pushButton_clicked()
{
    //saving
    Pop(money,Pop_index);
}


void MainWindow::on_pushButton_2_clicked()
{
    //withdrawal
    Push(money);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    cout<<arg1<<endl;
    money=arg1;
}




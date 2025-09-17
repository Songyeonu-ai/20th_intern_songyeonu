#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isclicked(false)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    for(int i=0;i<10;i++){
        timer[i]=new QElapsedTimer;
        count[i]=-1;
    }
    isLargeMode=false;
    if(isLargeMode){
        ui->pushButton_2->setText("ABC");
        ui->pushButton_8->setText("DEF");
        ui->pushButton_7->setText("GHI");
        ui->pushButton_6->setText("JKL");
        ui->pushButton_3->setText("MNO");
        ui->pushButton_4->setText("PQRS");
        ui->pushButton_5->setText("TUV");
        ui->pushButton_9->setText("WXZY");
    }
    else{
        ui->pushButton_2->setText("abc");
        ui->pushButton_8->setText("def");
        ui->pushButton_7->setText("ghi");
        ui->pushButton_6->setText("jkl");
        ui->pushButton_3->setText("mno");
        ui->pushButton_4->setText("pqrs");
        ui->pushButton_5->setText("tuv");
        ui->pushButton_9->setText("wxzy");
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::Put_text_3(int timernum, const char *num1, const char *num2, const char *num3){
    //버튼 다시눌림+1초안지남->전 글자 삭제
     if(timer[timernum]->isValid() && timer[timernum]->elapsed()<1000){
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
        cursor.removeSelectedText();
        ui->textEdit->setTextCursor(cursor);
        // 글자 순환
        count[timernum]++;
     }
    if(count[timernum]<0)count[timernum]=0;
    switch(count[timernum]%3){
        case 0: ui->textEdit->insertPlainText(num1); break;
        case 1: ui->textEdit->insertPlainText(num2); break;
        case 2: ui->textEdit->insertPlainText(num3); break;
    }
     // 버튼 눌림->무조건 타이머 초기화
     timer[timernum]->start();
}

void MainWindow::Put_text_4(int timernum, const char *num1, const char *num2, const char *num3, const char *num4){
    //버튼 다시눌림+1초안지남->전 글자 삭제
     if(timer[timernum]->isValid() && timer[timernum]->elapsed()<1000){
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
        cursor.removeSelectedText();
        ui->textEdit->setTextCursor(cursor);
        // 글자 순환
        count[timernum]++;
     }
    if(count[timernum]<0)count[timernum]=0;
    switch(count[timernum]%4){
        case 0: ui->textEdit->insertPlainText(num1); break;
        case 1: ui->textEdit->insertPlainText(num2); break;
        case 2: ui->textEdit->insertPlainText(num3); break;
        case 3: ui->textEdit->insertPlainText(num4); break;
    }
     // 버튼 눌림->무조건 타이머 초기화
     timer[timernum]->start();
}

void MainWindow::on_pushButton_clicked()
{
    //버튼1
    Put_text_4(0, ".", ",", "?", "!");

}

void MainWindow::on_pushButton_2_clicked()
{
    //버튼2
    if(isLargeMode)Put_text_3(1, "A", "B", "C");
    else Put_text_3(1, "a", "b", "c");
}


void MainWindow::on_pushButton_8_clicked()
{
    //버튼3
    if(isLargeMode)Put_text_3(2, "D", "E", "F");
    else Put_text_3(2, "d", "e", "f");
}


void MainWindow::on_pushButton_7_clicked()
{
    //버튼4
    if(isLargeMode)Put_text_3(3, "G", "H", "I");
    else Put_text_3(3, "g", "h", "i");
}


void MainWindow::on_pushButton_6_clicked()
{
    //버튼5
    if(isLargeMode)Put_text_3(4, "J", "K", "L");
    else Put_text_3(4, "j", "k", "l");
}


void MainWindow::on_pushButton_3_clicked()
{
    //버튼6
    if(isLargeMode)Put_text_3(5, "M", "N", "O");
    else Put_text_3(5, "m", "n", "o");
}


void MainWindow::on_pushButton_4_clicked()
{
    //버튼7
    if(isLargeMode)Put_text_4(6, "P", "Q", "R", "S");
    else Put_text_4(6, "p", "q", "r", "s");
}


void MainWindow::on_pushButton_5_clicked()
{
    //버튼8
    if(isLargeMode)Put_text_3(7, "T", "U", "V");
    else Put_text_3(7, "t", "u", "v");
}


void MainWindow::on_pushButton_9_clicked()
{
    //버튼9
    if(isLargeMode)Put_text_4(8, "W", "X", "Y", "Z");
    else Put_text_4(8, "w", "x", "y", "z");
}


void MainWindow::on_pushButton_10_clicked()
{
    //버튼0
}


void MainWindow::on_pushButton_14_clicked()
{
    //backspace
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
    cursor.removeSelectedText();
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_pushButton_15_clicked()
{
    //enter
    QString currentText = ui->textEdit->toPlainText();
    ofstream save;

        save.open("textbox.txt", std::ios::app); //더해서 쓰기 모드

       save<<currentText.toStdString()<<"\n";
       save<<endl;
       save.close();
    ui->textEdit->clear();
}


void MainWindow::on_pushButton_16_clicked()
{
    //shift
    if(!isLargeMode){
        ui->pushButton_2->setText("ABC");
        ui->pushButton_8->setText("DEF");
        ui->pushButton_7->setText("GHI");
        ui->pushButton_6->setText("JKL");
        ui->pushButton_3->setText("MNO");
        ui->pushButton_4->setText("PQRS");
        ui->pushButton_5->setText("TUV");
        ui->pushButton_9->setText("WXZY");
    }
    else{
        ui->pushButton_2->setText("abc");
        ui->pushButton_8->setText("def");
        ui->pushButton_7->setText("ghi");
        ui->pushButton_6->setText("jkl");
        ui->pushButton_3->setText("mno");
        ui->pushButton_4->setText("pqrs");
        ui->pushButton_5->setText("tuv");
        ui->pushButton_9->setText("wxzy");
    }
    isLargeMode=!isLargeMode;
}
void MainWindow::on_pushButton_16_released()
{
    ui->pushButton_16->setStyleSheet("background-color: rgb(237, 237, 237);color:rgb(93, 93, 93);border-radius: 5px;font: 24pt 'Ubuntu';");
}

void MainWindow::on_pushButton_16_pressed()
{
    ui->pushButton_16->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 24pt 'Ubuntu';");
}

void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 18pt 'Ubuntu';");
}

void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 18pt 'Ubuntu';");
}

void MainWindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}


void MainWindow::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}
void MainWindow::on_pushButton_5_released()
{
    ui->pushButton_5->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_5_pressed()
{
    ui->pushButton_5->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}
void MainWindow::on_pushButton_6_released()
{
    ui->pushButton_6->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_6_pressed()
{
    ui->pushButton_6->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}
void MainWindow::on_pushButton_7_released()
{
    ui->pushButton_7->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_7_pressed()
{
    ui->pushButton_7->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}
void MainWindow::on_pushButton_8_released()
{
    ui->pushButton_8->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_8_pressed()
{
    ui->pushButton_8->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_9_released()
{
    ui->pushButton_9->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_9_pressed()
{
    ui->pushButton_9->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_10_released()
{
    ui->pushButton_10->setStyleSheet("background-color: rgb(250, 250, 250);color:rgb(59, 59, 59);border-radius: 5px;font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_10_pressed()
{
    ui->pushButton_10->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 24pt 'Ubuntu';");
}

void MainWindow::on_pushButton_15_released()
{
    ui->pushButton_15->setStyleSheet("background-color: rgb(237, 237, 237);color:rgb(93, 93, 93);border-radius: 5px;font: 28pt 'Ubuntu';");
}

void MainWindow::on_pushButton_15_pressed()
{
    ui->pushButton_15->setStyleSheet("color: rgb(77, 175, 255); background-color: rgb(133, 131, 131); border-radius: 5px; font: 28pt 'Ubuntu';");
}



void MainWindow::on_pushButton_14_pressed()
{
    ui->pushButton_14->setStyleSheet("background-color: rgb(133, 131, 131); color:rgb(77, 175, 255); border-radius: 5px; font: 16pt 'Ubuntu';");
}
void MainWindow::on_pushButton_14_released()
{
    ui->pushButton_14->setStyleSheet("background-color: rgb(237, 237, 237); color:rgb(93, 93, 93); border-radius: 5px; font: 16pt 'Ubuntu';");
}

void MainWindow::on_pushButton_18_pressed()
{
    ui->pushButton_18->setStyleSheet("background-color: rgb(133, 131, 131); color:rgb(77, 175, 255); border-radius: 5px; font: 38pt 'Ubuntu';");
}
void MainWindow::on_pushButton_18_released()
{
    ui->pushButton_18->setStyleSheet("background-color: rgb(237, 237, 237); color:rgb(93, 93, 93); border-radius: 5px; font: 38pt 'Ubuntu';");
}

void MainWindow::on_pushButton_17_pressed()
{
    ui->pushButton_17->setStyleSheet("background-color: rgb(133, 131, 131); color:rgb(77, 175, 255); border-radius: 5px; font: 20pt 'Ubuntu';");
}
void MainWindow::on_pushButton_17_released()
{
    ui->pushButton_17->setStyleSheet("background-color: rgb(237, 237, 237); color:rgb(93, 93, 93); border-radius: 5px; font: 20pt 'Ubuntu';");
}




void MainWindow::on_pushButton_17_clicked()
{
    //,
    ui->textEdit->insertPlainText(",");
}


void MainWindow::on_pushButton_18_clicked()
{
    //space
    ui->textEdit->insertPlainText(" ");
}


void MainWindow::on_pushButton_12_clicked()
{
    //K/E
}


void MainWindow::on_pushButton_11_clicked()
{
    //특수문자->숫자
}




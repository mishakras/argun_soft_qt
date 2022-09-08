#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setText("Пройденный путь за 2000 миллисекунды");
    mouse = new Mouse_window;
    mouse->show();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Timer_timeout_handler()));
    timer->start(2000);
    connect(mouse,SIGNAL(sendData(int,int)),this,SLOT(mouse_move_handler(int,int)));
}

MainWindow::~MainWindow()
{
    delete mouse;
    delete ui;
}

void MainWindow::mouse_move_handler(int x,int y){
    times.append(QTime::currentTime());
    ui->lineEdit->setText(QString::number(x));
    ui->lineEdit_2->setText(QString::number(y));
    points.append(QPoint(x+50,y+100));
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!points.isEmpty()){
        while(!points.isEmpty())
            if (times[0].msecsTo(QTime::currentTime())>2000){
                times.removeFirst();
                points.removeFirst();
            }
            else
                break;
        double total_distance = 0;
        for (int i =0; i < points.size()-1;i++){
            painter.drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
            total_distance += qSqrt(qPow(points[i].x()-points[i+1].x(),2) + qPow(points[i].y()-points[i+1].y(),2));
        }
        ui->lineEdit_3->setText(QString::number(total_distance));
    }
}

void MainWindow::Timer_timeout_handler(){
    update();
    timer->start(2000);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mouse = new Mouse_window;
    mouse->show();
    ui->setupUi(this);
    connect(mouse,SIGNAL(sendData(int,int)),this,SLOT(mousedraw(int,int)));
}

MainWindow::~MainWindow()
{
    delete mouse;
    delete ui;
}

void MainWindow::mousedraw(int x,int y){
    points.prepend(QPoint(x+50,y+50));
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!points.isEmpty()){
        for (int i =0; i < points.size()-1;i++)
            painter.drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
}
}

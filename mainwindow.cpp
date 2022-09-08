#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setText("Пройденный путь за 2000 миллисекунды");
    ui->pushButton->setText("Текущий интервал = 2000");
    QAction *action;
    QMenu *main_Menu = new QMenu(this);
    action = new QAction("Загрузить настройки программы", this);
    connect(action, &QAction::triggered, this, &MainWindow::load_settings);
    main_Menu->addAction(action);
    action = new QAction("Сохранить настройки программы", this);
    connect(action, &QAction::triggered, this, &MainWindow::save_settings);
    main_Menu->addAction(action);
    action = new QAction("Ввести новый интервал времени", this);
    connect(action, &QAction::triggered, this, &MainWindow::get_time);
    main_Menu->addAction(action);
    action = new QAction("Ввести новое место сохранения файлов пути", this);
    connect(action, &QAction::triggered, this, &MainWindow::get_save_place);
    main_Menu->addAction(action);
    menuBar()->addMenu(main_Menu)->setText("Main menu");
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
    points.append(QPoint(x+150,y+150));
    while(!points.isEmpty())
        if (times[0].msecsTo(QTime::currentTime())>2000){
            times.removeFirst();
            points.removeFirst();
        }
        else
            break;
    double total_distance = 0;
    for (int i =0; i < points.size()-1;i++){
        total_distance += qSqrt(qPow(points[i].x()-points[i+1].x(),2) + qPow(points[i].y()-points[i+1].y(),2));
    }
    ui->lineEdit_3->setText(QString::number(total_distance));
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!points.isEmpty()){
        for (int i =0; i < points.size()-1;i++){
            painter.drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
        }
    }
}

void MainWindow::Timer_timeout_handler(){
    QString current_time = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    current_time.replace(":","_");
    current_time.replace("T"," ");
    current_time.replace("Z"," ");
    current_time.append(".txt");
    QFile fileOut(current_time);
    ui->label_4->setText(current_time);
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream writeStream(&fileOut);
            writeStream << ui->lineEdit_3->text();
            fileOut.close();
        }
    timer->start(2000);
}

void MainWindow::load_settings(){

}

void MainWindow::save_settings(){

}
void MainWindow::get_time(){

}
void MainWindow::get_save_place(){

}

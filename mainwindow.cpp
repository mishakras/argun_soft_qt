#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setText("Пройденный путь за 2000 миллисекунды");
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
    load_settings();
    connect(timer, SIGNAL(timeout()), this, SLOT(Timer_timeout_handler()));
    timer->start(time_interval);
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
        if (times[0].msecsTo(QTime::currentTime())>time_interval){
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

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawRect(148,148,400,300);
    if (!points.isEmpty()){
        for (int i =0; i < points.size()-1;i++){
            painter.drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
        }
    }
}

void MainWindow::Timer_timeout_handler(){
    QtConcurrent::run(write_to_file,ui->lineEdit_3->text(),save_place);
    update();
    timer->start(time_interval);
}

void MainWindow::write_to_file(QString distance, QString save_place){
    QString current_time = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    current_time.replace(":","_");
    current_time.replace("T"," ");
    current_time.replace("Z"," ");
    current_time.append(".txt");
    QFile fileOut(save_place+current_time);
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream writeStream(&fileOut);
            writeStream << distance;
            fileOut.close();
        }
}

void MainWindow::load_settings(){
    time_interval = 2000;
    save_place = "C:\\";
    QFile fileIn("settings.txt");
    if(fileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
            QString settings = fileIn.readAll();
            QStringList list = settings.split('\n');
            time_interval = list[0].toInt();
            save_place = list[1];
            fileIn.close();
        }
}

void MainWindow::save_settings(){
    QFile fileOut("settings.txt");
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream writeStream(&fileOut);
            writeStream << (QString::number(time_interval))+'\n';
            writeStream << save_place;
            fileOut.close();
        }
}

void MainWindow::get_time(){
    Dialog dlg("time", this );
    switch( dlg.exec() ) {
        case QDialog::Accepted:
            time_interval = dlg.getInput().toInt();
            break;
        default:
            break;
    }
}

void MainWindow::get_save_place(){
    Dialog dlg("save_place", this );
    switch( dlg.exec() ) {
        case QDialog::Accepted:
            save_place = dlg.getInput();
            break;
        default:
            break;
    }
}

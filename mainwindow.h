#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <mouse_window.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector<QPoint> points;
    QVector<QTime> times;
    void paintEvent(QPaintEvent *event) override;
    Mouse_window* mouse;
    Ui::MainWindow *ui;
    QTimer *timer;
    int time_interval;
    QString save_place;
public slots:
    void mouse_move_handler(int x,int y);
    void Timer_timeout_handler();
    void load_settings();
    void save_settings();
    void get_time();
    void get_save_place();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPoint>
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
    void paintEvent(QPaintEvent *event) override;
    Mouse_window* mouse;
    Ui::MainWindow *ui;

public slots:
    void mousedraw(int x,int y);
};
#endif // MAINWINDOW_H

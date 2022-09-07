#include "mouse_window.h"
#include "ui_mouse_window.h"

Mouse_window::Mouse_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mouse_window)
{
    setMouseTracking(true);
    ui->setupUi(this);
}

Mouse_window::~Mouse_window()
{
    delete ui;
}

void Mouse_window::mouseMoveEvent(QMouseEvent *moveevent) {
    emit sendData(moveevent->pos().x(),moveevent->pos().y());
}



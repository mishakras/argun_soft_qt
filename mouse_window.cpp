#include "mouse_window.h"
#include "ui_mouse_window.h"

Mouse_window::Mouse_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mouse_window)
{
    ui->setupUi(this);
}

Mouse_window::~Mouse_window()
{
    delete ui;
}

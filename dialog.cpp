#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QString value_type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    if (value_type == "time")
        ui->Enter_label->setText("Ввести временной интервал");
    else
        ui->Enter_label->setText("Ввести путь для сохранения файлов");
    connect(ui->Enter, SIGNAL( clicked() ), SLOT( accept() ) );
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getInput() {
    return ui->lineEdit->text();
}

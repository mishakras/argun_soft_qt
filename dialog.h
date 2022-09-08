#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QString value_type, QWidget *parent = nullptr);
    ~Dialog();
    QString getInput();

private:

    Ui::Dialog *ui;
};

#endif // DIALOG_H

#ifndef MOUSE_WINDOW_H
#define MOUSE_WINDOW_H

#include <QWidget>

namespace Ui {
class Mouse_window;
}

class Mouse_window : public QWidget
{
    Q_OBJECT

public:
    explicit Mouse_window(QWidget *parent = nullptr);
    ~Mouse_window();

private:
    Ui::Mouse_window *ui;
};

#endif // MOUSE_WINDOW_H

#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

private:
    Ui::AngadiMainWindow *ui;
};

#endif // ANGADIMAINWINDOW_H

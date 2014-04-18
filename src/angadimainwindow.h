#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include "customerform.h"

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
    CustomerForm *customerForm;
    bool tabLoadedStatus(QString tabName);

private slots:
    void exitMainwindow();
    void openCustomerTab();

};

#endif // ANGADIMAINWINDOW_H

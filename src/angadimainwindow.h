#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include "customerform.h"
#include "categoryform.h"

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

private slots:
    void on_mainTab_tabCloseRequested(int index);

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;
    CategoryForm *categoryForm;
    CustomerForm *customerForm;

private slots:
    void setupConnections();
    void exitMainwindow();
    void openCatagoryTab();
    void openCustomerTab();

};

#endif // ANGADIMAINWINDOW_H

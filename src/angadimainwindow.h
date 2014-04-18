#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include "catagoryform.h"

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
    void openCatagoryTab();
    void on_actionCreateItem_triggered();
     void on_mainTab_tabCloseRequested(int index);

     void on_actionExit_triggered();

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;
    CatagoryForm *obj_CatagoryForm;
};

#endif // ANGADIMAINWINDOW_H

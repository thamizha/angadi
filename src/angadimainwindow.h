#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include "customerform.h"
#include "categoryform.h"
#include "productform.h"
#include "lssbar.h"

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

signals:
    void exit();

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;
    CategoryForm *categoryForm;
    CustomerForm *customerForm;
    ProductForm *productForm;
    void openCustomerTab();
    void openProductTab();
    void openCategoryTab();

    void onCustomerTabClosed();
    void onProductTabClosed();
    void onCategoryTabClosed();

    void showRightDock(bool);
    Lssbar *lssbar;

private slots:
    void setupConnections();
    void exitApp();
    void openTab();
    void onCloseTab(int);
    void onTabChanged(int);
};

#endif // ANGADIMAINWINDOW_H

#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include "customerform.h"
#include "categoryform.h"
#include "productform.h"
#include "lssbar.h"
#include <models/categoriesmodel.h>
#include "models/productsmodel.h"

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

public slots:

signals:
    void exit();

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;
    CategoryForm *categoryForm;
    CustomerForm *customerForm;
    ProductForm *productForm;

    CategoriesModel *categoriesModel;
    ProductsModel *productsModel;

    void openCustomerTab();
    void openProductTab();
    void openCategoryTab();

    void onCustomerTabClosed();
    void onProductTabClosed();
    void onCategoryTabClosed();

    void setupConnections();
    void setupModels();

    void showRightDock(bool);
    Lssbar *lssbar;

    Connection conn;

private slots:    
    void exitApp();
    void openTab();
    void onCloseTab(int);
    void onTabChanged(int);
    void doubleClicked(QModelIndex index);
};

#endif // ANGADIMAINWINDOW_H

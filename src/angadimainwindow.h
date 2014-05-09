#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QTableWidget>

#include "lssbar.h"
#include "categoryform.h"
#include "productform.h"
#include "customerform.h"
#include "billform.h"
#include "models/categoriesmodel.h"
#include "models/productsmodel.h"
#include "models/customersmodel.h"
#include "models/billitemmodel.h"
#include "models/billmodel.h"

#include "qtrpt.h"

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentTab;
    QString categoryTabSearchTerm, productTabSearchTerm, customerTabSearchTerm, billTabCustomerSearchTerm;

public:
    explicit AngadiMainWindow(QWidget *parent = 0);
    ~AngadiMainWindow();

public slots:

signals:
    void exit();

private:
    bool tabLoadedStatus(QString tabName);
    Ui::AngadiMainWindow *ui;

    QTimer *timer;

    // initialization of toolbar actions
    QAction *actionCategory;
    QAction *actionProduct;
    QAction *actionCustomer;
    QAction *actionBillEntry;

    CategoryForm *categoryForm;
    ProductForm *productForm;
    CustomerForm *customerForm;
    BillForm *billForm;

    CategoriesModel *categoriesModel;
    ProductsModel *productsModel;
    CustomersModel *customersModel;
    BillModel *billModel;
    BillItemModel *billItemModel;

    // initialization of sort filter proxy model for all models.
    QSortFilterProxyModel *categoriesProxyModel;
    QSortFilterProxyModel *productsProxyModel;
    QSortFilterProxyModel *customersProxyModel;

    QtRPT *report;
    QTableWidget *tableWidget;

    void openCustomerTab();
    void openProductTab();
    void openCategoryTab();
    void openBillTab();

    void onCustomerTabClosed();
    void onProductTabClosed();
    void onCategoryTabClosed();
    void onBillTabClosed();

    void setupProperties();
    void setupConnections();
    void setupModels();

    void showRightDock(bool);
    Lssbar *lssbar;

private slots:    
    void exitApp();
    void openTab();
    void onCloseTab(int);
    void onTabChanged(int);
    void doubleClicked(QModelIndex index);
    void search(QString value);
    void moveUpDown(int indexOffset);
    void setSearchTerm(QString str);
    void setStatusBarText(QString statusBarText);
    void changeStatusMsgToDefault();
    void setStatusBarDefaultText();
    void changeLssBarSource();
    void showPeriodWiseReport();
    void setProductValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
};

#endif // ANGADIMAINWINDOW_H

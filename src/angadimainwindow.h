#ifndef ANGADIMAINWINDOW_H
#define ANGADIMAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QTableWidget>
#include <QPrinter>

#include "lssbar.h"
#include "categoryform.h"
#include "productform.h"
#include "customerform.h"
#include "billform.h"
#include "transactionform.h"
#include "models/categoriesmodel.h"
#include "models/productsmodel.h"
#include "models/customersmodel.h"
#include "models/billitemmodel.h"
#include "models/billmodel.h"
#include "models/transactionmodel.h"
#include <QHash>

#include "qtrpt.h"

namespace Ui {
class AngadiMainWindow;
}

class AngadiMainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentTab;
    QString categoryTabSearchTerm, productTabSearchTerm, customerTabSearchTerm, billTabCustomerSearchTerm, transactionTabSearchTerm;

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

    int billTabnumber;

    // initialization of toolbar actions
    QAction *actionCategory;
    QAction *actionProduct;
    QAction *actionCustomer;
    QAction *actionBillEntry;
    QAction *actionTransactionEntry;

    CategoryForm *categoryForm;
    ProductForm *productForm;
    CustomerForm *customerForm;
    QHash<QString,BillForm*> *billTabs;
    TransactionForm *transactionForm;

    CategoriesModel *categoriesModel;
    ProductsModel *productsModel;
    CustomersModel *customersModel;
    BillModel *billModel;
    BillItemModel *billItemModel;
    TransactionModel *transactionModel;

    QSqlTableModel *reportModel;

    // initialization of sort filter proxy model for all models.
    QSortFilterProxyModel *categoriesProxyModel;
    QSortFilterProxyModel *productsProxyModel;
    QSortFilterProxyModel *customersProxyModel;
    QSortFilterProxyModel *transactionProxyModel;

    QtRPT *report;
    QPrinter *printer;

    void openCustomerTab();
    void openProductTab();
    void openCategoryTab();
    void openBillTab();
    void openTransactionTab();

    void onCustomerTabClosed();
    void onProductTabClosed();
    void onCategoryTabClosed();
    void onBillTabClosed();
    void onTransactionTabClosed();

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
    void showProductListReport();
    void showCategoriesListReport();
    void showCustomersListReport();
    void setReportValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void settamil();
    void setenglish();
};

#endif // ANGADIMAINWINDOW_H

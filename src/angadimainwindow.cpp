/*****************************************************************************
 * catagoryform.cpp
 *
 * Created: 16/04/2014 by Manikk
 *
 * Copyright 2014 ThamiZha!. All rights reserved.
 *
 * Visit www.thamizha.com for more information.
 *
 * This file is a part of ThamiZha Angadi application.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *
 * Authors :
 * Manikk <manikk.h@gmail.com>
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "angadimainwindow.h"
#include "ui_angadimainwindow.h"
#include "angadiapp.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QMessageBox>
#include <QToolBar>
#include <qtranslator.h>
#include <QApplication>

#include <QSettings>

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    timer = new QTimer;

    lssbar = new Lssbar;

    billTabs = new QHash<QString,BillForm*>();
    billTabnumber = 0;

    connect(lssbar,SIGNAL(signalEdit(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
    connect(lssbar,SIGNAL(signalSearch(QString)),this,SLOT(search(QString)));
    connect(lssbar,SIGNAL(signalMoveUpDown(int)),this,SLOT(moveUpDown(int)));

    connect(ui->statusbar,SIGNAL(messageChanged(QString)),this,SLOT(changeStatusMsgToDefault()));
    connect(timer,SIGNAL(timeout()),this,SLOT(setStatusBarDefaultText()));

    // Hide rightdock widget on start
    showRightDock(false);
    ui->rightDock->setWidget(lssbar);

    ui->actionCreateCategory->setIcon(QIcon(":/images/toolbaricons/category.png"));
    ui->actionCreateProduct->setIcon(QIcon(":/images/toolbaricons/products.gif"));
    ui->actionCreateCustomer->setIcon(QIcon(":/images/toolbaricons/customer.png"));

    actionCategory = new QAction(QIcon(":/images/toolbaricons/category.png"), "&Category", this);
    actionProduct = new QAction(QIcon(":/images/toolbaricons/products.gif"), "&Product", this);
    actionCustomer = new QAction(QIcon(":/images/toolbaricons/customer.png"), "&Customer", this);
    actionBillEntry = new QAction(QIcon(":/images/toolbaricons/bill.png"), "&Bill", this);
    actionTransactionEntry = new QAction(QIcon(":/images/toolbaricons/bill.png"), "&Bill", this);

    QToolBar * toolBar= new QToolBar("Main Window Tool Bar");
    toolBar->addAction(actionCategory);
    toolBar->addAction(actionProduct);
    toolBar->addAction(actionCustomer);
    toolBar->addAction(actionBillEntry);
    toolBar->addAction(actionTransactionEntry);

    this->addToolBar(Qt::TopToolBarArea, toolBar);

    setupProperties();
    setupConnections();
    setupModels();

    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString content = settings.value("s_language","").toString();

    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
}

void AngadiMainWindow::setupProperties()
{
    //Set dynamic properties
    //TODO : Move the properties as ENUM insted of string
    ui->actionCreateCategory->setProperty("tabName","category");
    actionCategory->setProperty("tabName","category");

    ui->actionCreateProduct->setProperty("tabName","product");
    actionProduct->setProperty("tabName","product");

    ui->actionCreateCustomer->setProperty("tabName","customer");
    actionCustomer->setProperty("tabName","customer");

    ui->actionBillEntry->setProperty("tabName","bill");
    actionBillEntry->setProperty("tabName","bill");

    ui->actionTransactionEntry->setProperty("tabName","transaction");
    actionTransactionEntry->setProperty("tabName","transaction");
}

void AngadiMainWindow::setupConnections()
{
    connect(ui->actionCreateCategory, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(actionCategory,SIGNAL(triggered()),this,SLOT(openTab()));

    connect(ui->actionCreateProduct,SIGNAL(triggered()),this,SLOT(openTab()));
    connect(actionProduct,SIGNAL(triggered()),this,SLOT(openTab()));

    connect(ui->actionCreateCustomer, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(actionCustomer,SIGNAL(triggered()),this,SLOT(openTab()));

    connect(ui->actionBillEntry, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(actionBillEntry,SIGNAL(triggered()),this,SLOT(openTab()));

    connect(ui->actionTransactionEntry, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(actionTransactionEntry,SIGNAL(triggered()),this,SLOT(openTab()));

//    connect(ui->actionPeriod_Wise,SIGNAL(triggered()),this, SLOT(showPeriodWiseReport()));
    connect(ui->actionCategories_List,SIGNAL(triggered()),this, SLOT(showCategoriesListReport()));
    connect(ui->actionProduct_List,SIGNAL(triggered()),this, SLOT(showProductListReport()));
    connect(ui->actionCustomers_List,SIGNAL(triggered()),this, SLOT(showCustomersListReport()));

    connect(ui->mainTab,SIGNAL(tabCloseRequested(int)),SLOT(onCloseTab(int)));
    connect(ui->mainTab,SIGNAL(currentChanged(int)),SLOT(onTabChanged(int)));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApp()));

    connect(ui->actionTamil, SIGNAL(triggered()),this, SLOT(settamil()));
    connect(ui->actionEnglish, SIGNAL(triggered()),this, SLOT(setenglish()));
}


void AngadiMainWindow::settamil()
{
 QString app_path;
 app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
 QSettings settings(app_path,QSettings::NativeFormat);
 QString s_string = "tamil_language";
 settings.setValue("s_language",s_string);
// QString str_val = settings.value("s_language","").toString();

// qDebug() <<QApplication::applicationDirPath();
// qDebug() <<app_path;
// qDebug() << str_val;
}

void AngadiMainWindow::setenglish()
{
    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString s_string = "english_language";
    settings.setValue("s_language",s_string);
}


void AngadiMainWindow::setupModels()
{
    categoriesModel = new CategoriesModel;

    // Create new categoriesproxy model to filter sort functionalities
    categoriesProxyModel = new QSortFilterProxyModel; //initialization
    categoriesProxyModel->setSourceModel(categoriesModel); //set the source model to categories model
    categoriesProxyModel->setFilterKeyColumn(2); // set the filter to the name column
    categoriesProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    productsModel = new ProductsModel;

    // Create new productsproxy model to filter sort functionalities
    productsProxyModel = new QSortFilterProxyModel; //initialization
    productsProxyModel->setSourceModel(productsModel); //set the source model to categories model
    productsProxyModel->setFilterKeyColumn(2); // set the filter to the name column
    productsProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    customersModel = new CustomersModel;

    // Create new customersproxy model to filter sort functionalities
    customersProxyModel = new QSortFilterProxyModel; //initialization
    customersProxyModel->setSourceModel(customersModel); //set the source model to categories model
    customersProxyModel->setFilterKeyColumn(2); // set the filter to the name column
    customersProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    billModel = new BillModel;

    // Create new billproxy model to filter sort functionalities
//    billProxyModel = new QSortFilterProxyModel; //initialization
//    billProxyModel->setSourceModel(billModel); //set the source model to categories model
//    billProxyModel->setFilterKeyColumn(2); // set the filter to the name column
//    billProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    billItemModel = new BillItemModel;

    transactionModel = new TransactionModel;
    transactionProxyModel = new QSortFilterProxyModel; //initialization
    transactionProxyModel->setSourceModel(billModel); //set the source model to categories model
    transactionProxyModel->setFilterKeyColumn(1); // set the filter to the name column
    transactionProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

}

void AngadiMainWindow::exitApp()
{
    emit exit();
}

void AngadiMainWindow::openTab()
{
    QString tabName = sender()->property("tabName").toString();

    showRightDock(false);

    if(tabName == "customer"){
        openCustomerTab();
        showRightDock(true);
    }else if(tabName == "category"){
        openCategoryTab();
        showRightDock(true);
    }else if(tabName == "product"){
        openProductTab();
        showRightDock(true);
    }else if(tabName == "bill"){
        openBillTab();
        showRightDock(true);
    }else if(tabName == "transaction"){
        openTransactionTab();
        showRightDock(true);
    }
}

void AngadiMainWindow::openCategoryTab()
{
    QString tabName = "category";
    currentTab = tabName;

    bool found = tabLoadedStatus(tabName);
    if(found == false){
        categoryForm = new CategoryForm();
        categoryForm->setProperty("name", tabName);
        ui->mainTab->addTab(categoryForm, "Category");
        lssbar->lineEditSearch->setText("");

        setupModels();
        categoryForm->setModel(categoriesModel);
        categoryForm->clear();
        categoryForm->setFieldMaxLength();
        categoryTabSearchTerm = "";
        lssbar->lineEditSearch->setText(categoryTabSearchTerm);
    }
    connect(categoryForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(categoryForm,SIGNAL(signalFromCategoryForm()),lssbar,SLOT(setSearchFocus()));
    connect(categoryForm,SIGNAL(signalStatusBar(QString)),this,SLOT(setStatusBarText(QString)));
    connect(categoryForm,SIGNAL(signalUpdated()),this,SLOT(changeLssBarSource()));

    ui->mainTab->setCurrentWidget (categoryForm);
}

void AngadiMainWindow::openProductTab()
{
    QString tabName = "product";
    currentTab = tabName;

    bool found = tabLoadedStatus(tabName);
    if(found == false){
        productForm = new ProductForm();
        productForm->setProperty("name", tabName);
        ui->mainTab->addTab(productForm, "Product");
        lssbar->lineEditSearch->setText("");

        setupModels();
        productForm->setModel(productsModel);
        productForm->clear();
        productForm->setFieldMaxLength();
        productTabSearchTerm = "";
        lssbar->lineEditSearch->setText(productTabSearchTerm);
    }
    connect(productForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(productForm,SIGNAL(signalFromProductForm()),lssbar,SLOT(setSearchFocus()));
    connect(productForm,SIGNAL(signalStatusBar(QString)),this,SLOT(setStatusBarText(QString)));
    connect(productForm,SIGNAL(signalUpdated()),this,SLOT(changeLssBarSource()));

    ui->mainTab->setCurrentWidget (productForm);
}

void AngadiMainWindow::openCustomerTab()
{
    QString tabName = "customer";
    currentTab = tabName;

    bool found = tabLoadedStatus(tabName);
    if(found == false){
        customerForm = new CustomerForm();
        customerForm->setProperty("name", tabName);
        ui->mainTab->addTab(customerForm, "Customer");
        lssbar->lineEditSearch->setText("");

        setupModels();
        customerForm->setModel(customersModel);
        customerForm->clear();
        customerForm->setFieldMaxLength();
        customerTabSearchTerm = "";
        lssbar->lineEditSearch->setText(customerTabSearchTerm);
    }
    connect(customerForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(customerForm,SIGNAL(signalFromCustomerForm()),lssbar,SLOT(setSearchFocus()));
    connect(customerForm,SIGNAL(signalStatusBar(QString)),this,SLOT(setStatusBarText(QString)));
    connect(customerForm,SIGNAL(signalUpdated()),this,SLOT(changeLssBarSource()));

    ui->mainTab->setCurrentWidget (customerForm);
}

void AngadiMainWindow::openBillTab()
{
    QString tabName;

    billTabnumber = billTabnumber+1;
    tabName = "bill#"+QString::number(billTabnumber);
    currentTab = tabName;

    billTabs->insert(tabName,new BillForm());
    billTabs->value(tabName)->setProperty("name",tabName);
    ui->mainTab->addTab(billTabs->value(tabName),"Bill");

    connect(billTabs->value(tabName),SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(billTabs->value(tabName),SIGNAL(signalFromBillForm()),lssbar,SLOT(setSearchFocus()));
    connect(billTabs->value(tabName),SIGNAL(signalCustomerNameFocused()),this,SLOT(changeLssBarSource()));

    setupModels();
    billTabs->value(tabName)->setModel(billModel, billItemModel, productsModel, customersModel);
    billTabs->value(tabName)->clear();

    billTabCustomerSearchTerm = "";
    lssbar->lineEditSearch->setText(billTabCustomerSearchTerm);
    lssbar->setModel(billModel);

    ui->mainTab->setCurrentWidget (billTabs->value(tabName));
    billTabs->value(tabName)->setCodeFocus();
}

void AngadiMainWindow::openTransactionTab()
{
    QString tabName = "transaction";
    currentTab = tabName;

    bool found = tabLoadedStatus(tabName);
    if(found == false){
        transactionForm = new TransactionForm();
        transactionForm->setProperty("name", tabName);
        ui->mainTab->addTab(transactionForm, "Transaction");
        lssbar->lineEditSearch->setText("");

        setupModels();
        transactionForm->setModel(transactionModel);
        transactionForm->clear();
        transactionForm->setFieldMaxLength();
        transactionTabSearchTerm = "";
        lssbar->lineEditSearch->setText(customerTabSearchTerm);
    }
    connect(transactionForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(transactionForm,SIGNAL(signalFromTransactionForm()),lssbar,SLOT(setSearchFocus()));
    connect(transactionForm,SIGNAL(signalStatusBar(QString)),this,SLOT(setStatusBarText(QString)));
    connect(transactionForm,SIGNAL(signalUpdated()),this,SLOT(changeLssBarSource()));

    ui->mainTab->setCurrentWidget (transactionForm);
}

bool AngadiMainWindow::tabLoadedStatus(QString tabName)
{
    bool status = false;        
    for(int i = 0; i < ui->mainTab->count(); i++)
    {
        if(ui->mainTab->widget(i)->property("name").toString() == tabName){
            status = true;
        }
    }
    return status;
}


void AngadiMainWindow::onCloseTab(int index)
{
    QWidget *widget = ui->mainTab->widget(index);
    QString tabName = widget->property("name").toString();
    //qDebug() << "close tab requested :::> " << tabName;

    if(ui->mainTab->count() == 1){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Angadi","Are you sure you want to quit?",QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            exitApp();
        }
    }else{
        ui->mainTab->removeTab(index);
        if(tabName == "category"){
            onCategoryTabClosed();

        }else if(tabName == "customer"){
            onCustomerTabClosed();

        }else if(tabName == "product"){
            onProductTabClosed();
        }else if(tabName.contains("bill#", Qt::CaseInsensitive)){
            billTabs->remove(tabName);
        }else if(tabName == "transaction"){
            onTransactionTabClosed();
        }
    }
}

void AngadiMainWindow::onCustomerTabClosed()
{
    //qDebug() << "On Customer Tab closed called ";
}

void AngadiMainWindow::onCategoryTabClosed()
{
    //qDebug() << "On Category Tab closed called ";
}

void AngadiMainWindow::onProductTabClosed()
{
    //qDebug() << "On Product Tab closed called ";
}

void AngadiMainWindow::onBillTabClosed()
{
    //qDebug() << "On Bill Tab closed called ";
}

void AngadiMainWindow::onTransactionTabClosed()
{
    //qDebug() << "On Transaction Tab closed called ";
}

void AngadiMainWindow::showRightDock(bool state)
{
    ui->rightDock->setVisible(state);
}

void AngadiMainWindow::onTabChanged(int index){
    setupModels();
    QWidget *widget = ui->mainTab->widget(index);
    QString tabName = widget->property("name").toString();

    currentTab = tabName;

    showRightDock(false);
    if(tabName == "category"){
//        categoryForm->setModel(categoriesModel);
//        categoryForm->clear();
        lssbar->setModel(categoriesModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(categoryTabSearchTerm);

    }else if(tabName == "product"){
//        productForm->setModel(productsModel);
//        productForm->clear();
        productForm->setComboSource();
        lssbar->setModel(productsModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(productTabSearchTerm);

    }else if(tabName == "customer"){
//        customerForm->setModel(customersModel);
//        customerForm->clear();
        lssbar->setModel(customersModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(customerTabSearchTerm);

    }else if(tabName == "transaction"){
        lssbar->setModel(transactionModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(transactionTabSearchTerm);

    }else{
        if(tabName.contains("bill#", Qt::CaseInsensitive)){
//            billTabs->value(tabName)->setModel(billModel, productsModel, customersModel);
//            billTabs->value(tabName)->clear();
            if(billTabs->value(tabName)->modelFlag == 1){
                lssbar->setModel(customersModel);
            }else if(billTabs->value(tabName)->modelFlag == 2){
                lssbar->setModel(productsModel);
            }else {
                lssbar->setModel(billModel);
            }
            showRightDock(true);
            lssbar->lineEditSearch->setText(billTabCustomerSearchTerm);
        }
    }
}

void AngadiMainWindow::doubleClicked(QModelIndex index)
{
    if(currentTab == "category"){
        if(index.row() >= 0){
            categoryForm->setMapperIndex(index);
            categoryForm->setNameFocus();
        }else{
            categoryForm->setNameFocus();
        }

     }else if(currentTab == "product"){
        if(index.row() >= 0){
            productForm->setMapperIndex(index);
            productForm->setCodeFocus();
        }else{
            productForm->setNameFocus();
        }

     }else if(currentTab == "customer"){
        if(index.row() >= 0){
            customerForm->setMapperIndex(index);
            customerForm->setCodeFocus();
        }else{
            customerForm->setNameFocus();
        }

    }else if(currentTab == "transaction"){
        if(index.row() >= 0){
            transactionForm->setMapperIndex(index);
            transactionForm->setCodeFocus();
        }else{
            transactionForm->setNameFocus();
        }

    }else if(currentTab.contains("bill#", Qt::CaseInsensitive)){
        if(index.row() >= 0){
            if(billTabs->value(currentTab)->modelFlag == 1){
                billTabs->value(currentTab)->setMapperIndex(index);
                billTabs->value(currentTab)->setProductFocus();
            }else if(billTabs->value(currentTab)->modelFlag == 2){
                billTabs->value(currentTab)->setMapperIndex(index);
                billTabs->value(currentTab)->setQuantityFocus();
            }else{
                billTabs->value(currentTab)->setCodeFocus();
                billTabs->value(currentTab)->setMapperIndex(index);
            }
        }else{
//           billForm->setCodeFocus();
            billTabs->value(currentTab)->productFormClearForSearch();
            billTabs->value(currentTab)->setProductFocus();
        }
    }
}

// search the model for the given string
void AngadiMainWindow::search(QString value)
{
    if(currentTab == "category"){
        categoriesProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on te categories proxy model
        int indexOffset = 0; //reset the indexOffset
        QModelIndex proxyIndex, index; //Initialization of new index
        proxyIndex = categoriesProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
        index = categoriesProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
        lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
        categoryTabSearchTerm = value;

     }else if(currentTab == "product"){
        productsProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on te products proxy model
        int indexOffset = 0; //reset the indexOffset
        QModelIndex proxyIndex, index; //Initialization of new index
        proxyIndex = productsProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
        index = productsProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
        lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
        productTabSearchTerm = value;

     }else if(currentTab == "customer"){
        customersProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on te customers proxy model
        int indexOffset = 0; //reset the indexOffset
        QModelIndex proxyIndex, index; //Initialization of new index
        proxyIndex = customersProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
        index = customersProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
        lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
        customerTabSearchTerm = value;

    }else if(currentTab == "transaction"){
       transactionProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on the customers proxy model
       int indexOffset = 0; //reset the indexOffset
       QModelIndex proxyIndex, index; //Initialization of new index
       proxyIndex = transactionProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
       index = transactionProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
       lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
       transactionTabSearchTerm = value;

    }else if(currentTab.contains("bill#", Qt::CaseInsensitive)){
        if(billTabs->value(currentTab)->modelFlag == 1){
            customersProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on te customers proxy model
            int indexOffset = 0; //reset the indexOffset
            QModelIndex proxyIndex, index; //Initialization of new index
            proxyIndex = customersProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
            index = customersProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
            lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
            billTabCustomerSearchTerm = value;
        }else if(billTabs->value(currentTab)->modelFlag == 2){
            productsProxyModel->setFilterRegExp(QString("%2").arg(value)); // set the filter on te products proxy model
            int indexOffset = 0; //reset the indexOffset
            QModelIndex proxyIndex, index; //Initialization of new index
            proxyIndex = productsProxyModel->index(indexOffset,0); // get the index of the first row on the filtered proxy model
            index = productsProxyModel->mapToSource(proxyIndex); // get the source index of the current filtered proxy model
            lssbar->setFilterSelect(index,indexOffset); //set the selection to the current filtered proxy model by sending corresponding source model index
            billTabCustomerSearchTerm = value;
        }
    }
}

// move the selection up/down within the filtered proxy model
void AngadiMainWindow::moveUpDown(int indexOffset)
{
    if(currentTab == "category"){
        QModelIndex proxyIndex,index; //intialize the model index
        //qint8 rowCount = categoriesProxyModel->rowCount(); // get the proxy model total row count
        qint8 rowCount = categoriesModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset = rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        index = categoriesModel->index(indexOffset,0);
        //proxyIndex = categoriesProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        //index = categoriesProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }else if(currentTab == "product"){
        QModelIndex proxyIndex,index; //intialize the model index
        //qint8 rowCount = productsProxyModel->rowCount(); // get the proxy model total row count
        qint8 rowCount = productsModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset=rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        index = productsModel->index(indexOffset,0);
        //proxyIndex = productsProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        //index = productsProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }else if(currentTab == "customer"){
        QModelIndex proxyIndex,index; //intialize the model index
        //qint8 rowCount = customersProxyModel->rowCount(); // get the proxy model total row count
        qint8 rowCount = customersModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset=rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        index = customersModel->index(indexOffset,0);
        //proxyIndex = customersProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        //index = customersProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }
}

void AngadiMainWindow::setSearchTerm(QString str)
{
    lssbar->lineEditSearch->setText(str);
}

void AngadiMainWindow::setStatusBarText(QString statusBarText)
{
    this->statusBar()->showMessage(statusBarText);
}

void AngadiMainWindow::setStatusBarDefaultText()
{
    this->statusBar()->showMessage("Ready");
}

void AngadiMainWindow::changeStatusMsgToDefault()
{
    // Status bar message to default
    timer->start(3000);
}

void AngadiMainWindow::changeLssBarSource()
{
    if(currentTab == "category"){
        lssbar->setModel(categoriesModel);

    }else if(currentTab == "product"){
        lssbar->setModel(productsModel);

    }else if(currentTab == "customer"){
        lssbar->setModel(customersModel);

    }else if(currentTab == "transaction"){
        lssbar->setModel(transactionModel);

    }else if(currentTab.contains("bill#", Qt::CaseInsensitive)){
        if(billTabs->value(currentTab)->modelFlag==1){
            lssbar->setModel(customersModel);
        }else if(billTabs->value(currentTab)->modelFlag == 2){
            lssbar->setModel(productsModel);
        }else{
            lssbar->setModel(billModel);
        }
        showRightDock(true);
        lssbar->lineEditSearch->setText(billTabCustomerSearchTerm);
    }
}

void AngadiMainWindow::showCategoriesListReport()
{
    QString fileName = "./reports/categories_list.xml";
    report = new QtRPT(this);
//    report->setBackgroundImage(QPixmap("./qt_background_portrait.png"));

    reportModel = new QSqlTableModel;
    reportModel->setTable("categories");
    reportModel->setFilter("categories.status = 'A'");
    reportModel->setSort(reportModel->fieldIndex("code"),Qt::AscendingOrder);
    reportModel->select();
    report->recordCount << reportModel->rowCount();

    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setReportValue(int&, QString&, QVariant&, int)));
//    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
//                     this, SLOT(setProductValueImage(int&, QString&, QImage&, int)));
    //report->setCallbackFunc(getReportValue);

    printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    //printer->setPaperSize(QPrinter::B0);
    //qDebug() << printer->paperSize();
    printer->setFullPage(true);

    report->printExec(true);
}

void AngadiMainWindow::showProductListReport()
{
    QString fileName = "./reports/product_list.xml";
    report = new QtRPT(this);
//    report->setBackgroundImage(QPixmap("./qt_background_portrait.png"));

    reportModel = new QSqlTableModel;
    reportModel->setTable("products");
    reportModel->setFilter("products.status = 'A'");
    reportModel->setSort(reportModel->fieldIndex("code"),Qt::AscendingOrder);
    reportModel->select();
    report->recordCount << reportModel->rowCount();

    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setReportValue(int&, QString&, QVariant&, int)));
//    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
//                     this, SLOT(setProductValueImage(int&, QString&, QImage&, int)));
    //report->setCallbackFunc(getReportValue);

    printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    //printer->setPaperSize(QPrinter::B0);
    //qDebug() << printer->paperSize();
    printer->setFullPage(true);

    report->printExec(true);
}

void AngadiMainWindow::showCustomersListReport()
{
    QString fileName = "./reports/customers_list.xml";
    report = new QtRPT(this);
//    report->setBackgroundImage(QPixmap("./qt_background_portrait.png"));

    reportModel = new QSqlTableModel;
    reportModel->setTable("customers");
    reportModel->setFilter("customers.status = 'A'");
    reportModel->setSort(reportModel->fieldIndex("code"),Qt::AscendingOrder);
    reportModel->select();
    report->recordCount << reportModel->rowCount();

    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setReportValue(int&, QString&, QVariant&, int)));
//    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
//                     this, SLOT(setProductValueImage(int&, QString&, QImage&, int)));
    //report->setCallbackFunc(getReportValue);

    printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    //printer->setPaperSize(QPrinter::B0);
    //qDebug() << printer->paperSize();
    printer->setFullPage(true);

    report->printExec(true);
}

void AngadiMainWindow::setReportValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    Q_UNUSED(reportPage);
    QSqlRecord record = reportModel->record(recNo);
    if (paramName == "Code") {
        if (record.value("code").toString().length() == 0) return;
        paramValue = record.value("code").toString();
    }
    if (paramName == "Name") {
        if (record.value("name").toString().length() == 0) return;
        paramValue = record.value("name").toString();
    }
}

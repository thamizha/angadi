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
 *****************************************************************************/

#include "angadimainwindow.h"
#include "ui_angadimainwindow.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QMessageBox>

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    /*QDockWidget *dock = new QDockWidget(tr("Search Bar"), this);
    QLineEdit *lineEditCode= new QLineEdit(dock);
    QLineEdit *lineEditName= new QLineEdit(dock);
    dock->setWidget(lineEditCode);
    dock->setWidget(lineEditName);
    addDockWidget(Qt::RightDockWidgetArea, dock);*/

    lssbar = new Lssbar;

    connect(lssbar,SIGNAL(signalEdit(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
    connect(lssbar,SIGNAL(signalSearch(QString)),this,SLOT(search(QString)));
    connect(lssbar,SIGNAL(signalMoveUpDown(int)),this,SLOT(moveUpDown(int)));

    //Hide rightdock widget on start
    showRightDock(false);
    ui->rightDock->setWidget(lssbar);


    //Set dynamic properties
    //TODO : Move the properties as ENUM insted of string
    ui->actionCreateCategory->setProperty("tabName","category");
    ui->actionCreateCustomer->setProperty("tabName","customer");
    ui->actionCreateProduct->setProperty("tabName","product");

    setupConnections();
    setupModels();
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
}

void AngadiMainWindow::setupConnections()
{
    connect(ui->actionCreateCategory, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(ui->actionCreateCustomer, SIGNAL(triggered()), this, SLOT(openTab()));
    connect(ui->actionCreateProduct,SIGNAL(triggered()),this,SLOT(openTab()));

    connect(ui->mainTab,SIGNAL(tabCloseRequested(int)),SLOT(onCloseTab(int)));
    connect(ui->mainTab,SIGNAL(currentChanged(int)),SLOT(onTabChanged(int)));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApp()));
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
}

void AngadiMainWindow::exitApp()
{
    emit exit();
}

void AngadiMainWindow::openTab()
{
    QString tabName = sender()->property("tabName").toString();

    if(tabName == "customer" ||
       tabName == "category" ||
       tabName == "product"){
        showRightDock(true);
    }else{
        showRightDock(false);
    }

    if(tabName == "customer"){
        openCustomerTab();
    }else if(tabName == "category"){
        openCategoryTab();
    }else if(tabName == "product"){
        openProductTab();
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
    }
    connect(categoryForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(categoryForm,SIGNAL(signalFromCategoryForm()),lssbar,SLOT(setSearchFocus()));

    categoryForm->setModel(categoriesModel);
    categoryForm->clear();
    ui->mainTab->setCurrentWidget (categoryForm);
//    categoryForm->setCodeFocus();

//    lssbar->setModel(categoriesModel);
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
    }
    connect(productForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(productForm,SIGNAL(signalFromProductForm()),lssbar,SLOT(setSearchFocus()));

    productForm->setModel(productsModel);
    productForm->clear();
    ui->mainTab->setCurrentWidget (productForm);
    productForm->setFieldMaxLength();

//    productForm->setCodeFocus();

//    lssbar->setModel(productsModel);
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
    }
    connect(customerForm,SIGNAL(signalName(QString)),this,SLOT(setSearchTerm(QString)));
    connect(customerForm,SIGNAL(signalFromCustomerForm()),lssbar,SLOT(setSearchFocus()));

    customerForm->setModel(customersModel);
    customerForm->clear();
    ui->mainTab->setCurrentWidget (customerForm);
//    customerForm->setCodeFocus();

//    lssbar->setModel(customersModel);
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

void AngadiMainWindow::showRightDock(bool state)
{
    ui->rightDock->setVisible(state);
}

void AngadiMainWindow::onTabChanged(int index){
    QWidget *widget = ui->mainTab->widget(index);
    QString tabName = widget->property("name").toString();

    currentTab = tabName;

    showRightDock(false);
    if(tabName == "category"){
        categoryForm->setModel(categoriesModel);
        categoryForm->clear();
        lssbar->setModel(categoriesModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(categoryTabSearchTerm);

    }else if(tabName == "product"){
        productForm->setModel(productsModel);
        productForm->clear();
        lssbar->setModel(productsModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(productTabSearchTerm);

    }else if(tabName == "customer"){
        customerForm->setModel(customersModel);
        customerForm->clear();
        lssbar->setModel(customersModel);
        showRightDock(true);
        lssbar->lineEditSearch->setText(customerTabSearchTerm);
    }
}

void AngadiMainWindow::doubleClicked(QModelIndex index)
{
    if(currentTab == "category"){
        categoryForm->setMapperIndex(index);
        categoryForm->setCodeFocus();

     }else if(currentTab == "product"){
        productForm->setMapperIndex(index);
        productForm->setCodeFocus();

     }else if(currentTab == "customer"){
        customerForm->setMapperIndex(index);
        customerForm->setCodeFocus();

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

     }
}

// move the selection up/down within the filtered proxy model
void AngadiMainWindow::moveUpDown(int indexOffset)
{
    if(currentTab == "category"){
        QModelIndex proxyIndex,index; //intialize the model index
        qint8 rowCount = categoriesProxyModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset=rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        proxyIndex = categoriesProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        index = categoriesProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }else if(currentTab == "product"){
        QModelIndex proxyIndex,index; //intialize the model index
        qint8 rowCount = productsProxyModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset=rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        proxyIndex = productsProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        index = productsProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }else if(currentTab == "customer"){
        QModelIndex proxyIndex,index; //intialize the model index
        qint8 rowCount = customersProxyModel->rowCount(); // get the proxy model total row count
        if(indexOffset < 0) // if the index model is less than 0, mark the index to the last row
            indexOffset=rowCount-1;
        else if(indexOffset > rowCount-1) // if the indexmodel is greater than row count reset it to zero
            indexOffset = 0;
        else
            indexOffset = indexOffset;

        proxyIndex = customersProxyModel->index(indexOffset,0); //move the index to the proxy model row specified by offset
        index = customersProxyModel->mapToSource(proxyIndex); //get the source index of the current proxy model index
        lssbar->setFilterSelect(index,indexOffset); // set the selection to the current source index

     }
}

void AngadiMainWindow::setSearchTerm(QString str)
{
    lssbar->lineEditSearch->setText(str);
}

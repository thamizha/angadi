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
#include "lssbar.h"
#include "models/categoriesmodel.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QMessageBox>

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    lssbar = new Lssbar;

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
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            categoryForm = new CategoryForm();
            categoryForm->setProperty("name", tabName);
            ui->mainTab->addTab(categoryForm, "Category");
        }
    }else{
        categoryForm = new CategoryForm();
        categoryForm->setProperty("name", tabName);
        ui->mainTab->addTab(categoryForm, "Category");
    }
    ui->mainTab->setCurrentWidget (categoryForm);
    categoryForm->setCodeFocus();    
    categoryForm->setModel(categoriesModel);

    lssbar->setModel(categoriesModel);
}

void AngadiMainWindow::openProductTab()
{
    QString tabName = "product";
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            productForm = new ProductForm();
            productForm->setProperty("name", tabName);
            ui->mainTab->addTab(productForm, "Product");
        }
    }else{
        productForm = new ProductForm();
        productForm->setProperty("name", tabName);
        ui->mainTab->addTab(productForm, "Product");
    }
    ui->mainTab->setCurrentWidget (productForm);
    productForm->setCodeFocus();
}

void AngadiMainWindow::openCustomerTab()
{
    QString tabName = "customer";
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            customerForm = new CustomerForm();
            customerForm->setProperty("name", tabName);
            ui->mainTab->addTab(customerForm, "Customer");
        }
    }else{
        customerForm = new CustomerForm();
        customerForm->setProperty("name", tabName);
        ui->mainTab->addTab(customerForm, "Customer");
    }
    ui->mainTab->setCurrentWidget (customerForm);
    customerForm->setCodeFocus();
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

    //qDebug() << "Current Active Tab ::::> " << tabName;

    if(tabName == "customer" ||
       tabName == "category" ||
       tabName == "product"){
        showRightDock(true);
    }else{
        showRightDock(false);
    }
}


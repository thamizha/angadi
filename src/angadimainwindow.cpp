#include "angadimainwindow.h"
#include "ui_angadimainwindow.h"

#include <QMetaObject>
#include <QMetaProperty>
#include<QDebug>

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    //Hide rightdock widget on start
    ui->rightDock->setVisible(false);

    setupConnections();
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
}

void AngadiMainWindow::setupConnections()
{
    connect(ui->actionCreateCategory, SIGNAL(triggered()), this, SLOT(openCatagoryTab()));
    connect(ui->actionCreateCustomer, SIGNAL(triggered()), this, SLOT(openCustomerTab()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitMainwindow()));
}

void AngadiMainWindow::exitMainwindow()
{
    this->close();
}

void AngadiMainWindow::openCustomerTab()
{
    QString tabName = "Customer";
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            customerForm = new CustomerForm();
            customerForm->setProperty("name", tabName);
            ui->mainTab->addTab(customerForm, tabName);
        }
    }else{
        customerForm = new CustomerForm();
        customerForm->setProperty("name", tabName);
        ui->mainTab->addTab(customerForm, tabName);
    }
    ui->mainTab->setCurrentWidget (customerForm);
}

void AngadiMainWindow::openCatagoryTab()
{
    QString tabName = "Category";
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            categoryForm = new CategoryForm();
            categoryForm->setProperty("name", tabName);
            ui->mainTab->addTab(categoryForm, tabName);
        }
    }else{
        categoryForm = new CategoryForm();
        categoryForm->setProperty("name", tabName);
        ui->mainTab->addTab(categoryForm, tabName);
    }
    ui->mainTab->setCurrentWidget (categoryForm);
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

void AngadiMainWindow::on_mainTab_tabCloseRequested(int index)
{
    //qDebug() << index;
    if(index != 0)
        ui->mainTab->removeTab(index);
}

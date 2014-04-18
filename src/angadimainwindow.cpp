#include "angadimainwindow.h"
#include "ui_angadimainwindow.h"

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    //Hide rightdock widget on start
    ui->rightDock->setVisible(false);

    connect(ui->actionCreateCustomer, SIGNAL(triggered()), this, SLOT(openCustomerTab()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitMainwindow()));
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
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

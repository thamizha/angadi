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
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
}

void AngadiMainWindow::on_actionCreateItem_triggered()
{
    openCatagoryTab();
}

void AngadiMainWindow::openCatagoryTab()
{
    QString tabName = "Catagory";
    if(ui->mainTab->count() > 1){
        bool found = tabLoadedStatus(tabName);
        if(found == false){
            obj_CatagoryForm = new CatagoryForm();
            obj_CatagoryForm->setProperty("name", tabName);
            ui->mainTab->addTab(obj_CatagoryForm, tabName);
        }
    }else{
        obj_CatagoryForm = new CatagoryForm();
        obj_CatagoryForm->setProperty("name", tabName);
        ui->mainTab->addTab(obj_CatagoryForm, tabName);
    }
    ui->mainTab->setCurrentWidget (obj_CatagoryForm);
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

void AngadiMainWindow::on_actionExit_triggered()
{
    close();
}

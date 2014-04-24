/*****************************************************************************
 * catagoryform.cpp
 *
 * Created: 18/04/2014 by gvijaydhanasekaran
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
 * gvijaydhanasekaran <vijay.kuruntham@gmail.com>
 *****************************************************************************/

#include "categoryform.h"
#include "ui_categoryform.h"
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>

CategoryForm::CategoryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryForm)
{
    ui->setupUi(this);
    ui->labelCodeValid->hide();
    ui->labelNameValid->hide();

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));

    dataMapper = new QDataWidgetMapper(this);

    // Enter key to focus next control
    connect(ui->lineEditCode,SIGNAL(returnPressed()),ui->lineEditName,SLOT(setFocus()));
    connect(ui->lineEditName,SIGNAL(returnPressed()),ui->pushButtonSave,SLOT(setFocus()));	
    connect(ui->lineEditCode,SIGNAL(editingFinished()),this,SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),this,SLOT(nameValid()));
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

void CategoryForm::save()
{
    // Initialization of local variables
    int validError = 0;
    QString errors = "";

    // Initialization of message box
    QMessageBox msgBox;
    msgBox.setText("Validation Error in this forms. Please correct the form and resubmit it");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // validate code field
    if(!CategoryForm::codeValid())
    {
        validError=1;
        errors.append("\nThe Category Code field may be empty or contains text or greater than 10000");
    }

    // validate name field
    if(!CategoryForm::nameValid())
    {
        validError=1;
        errors.append("\n\nThe Category Name field may be empty or exceeds the limit 20 characters");
    }

    // save the form if there is no errors
    if(validError==0)
    {
        /*int rowIndex = categoriesModel->rowCount();
        qDebug() << "rowIndex :::>" << rowIndex;
        categoriesModel->insertRow(rowIndex);
        categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("code")),ui->lineEditCode->text());
        categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("name")),ui->lineEditName->text());
        categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("createdDate")),"2014-04-22 00:00:00");
        if(categoriesModel->submit())
            qDebug() << "Success";
        else
            qDebug() << "failed";
        */
        clear();
        setCodeFocus();
        bool status;

        qDebug() << dataMapper->currentIndex();
        dataMapper->toLast();
        status = dataMapper->submit();

        if(status == true)
        {
            dataMapper->toLast();
            qDebug() << categoriesModel->data(categoriesModel->index(dataMapper->currentIndex(),categoriesModel->fieldIndex("code")));
            categoriesModel->submitAll();
            qDebug() << categoriesModel->lastError().text();
        }
    }

    // display the error message if there is any errors
    else
    {
        msgBox.setInformativeText(errors);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Ok:
               ui->lineEditCode->setFocus();
               ui->lineEditCode->selectAll();
               break;
           default:
               // should never be reached
               break;
         }
    }

    /*int rowIndex = categoriesModel->rowCount();
    qDebug() << "rowIndex :::>" << rowIndex;
    categoriesModel->insertRow(rowIndex);
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("code")),ui->lineEditCode->text());
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("name")),ui->lineEditName->text());
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("createdDate")),"2014-04-22 00:00:00");
    categoriesModel->submit();*/
    //clear();
    //setCodeFocus();
}

void CategoryForm::setCodeFocus()
{
    ui->lineEditCode->setFocus();

}

void CategoryForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
}

void CategoryForm::setModel(CategoriesModel *model){
    categoriesModel = model;
    dataMapper->setModel(categoriesModel);
    dataMapper->addMapping(ui->lineEditCode,categoriesModel->fieldIndex("code"));
    dataMapper->addMapping(ui->lineEditName,categoriesModel->fieldIndex("name"));
    dataMapper->toLast();
}

// function to validate code field
bool CategoryForm::codeValid(){
    bool status =false;
    FormValidation formValidation;
    if(formValidation.intValid(ui->lineEditCode->text()))
    {
        ui->labelCodeValid->hide();
        status = true;
    }
    else
    {
        ui->labelCodeValid->show();
        status= false;
    }
    return status;
}

//function to validate name field
bool CategoryForm::nameValid(){
    bool status = false;
    FormValidation formValidation;
    if(formValidation.textValid(ui->lineEditName->text(),20))
    {
        status = true;
        ui->labelNameValid->hide();
    }
    else
    {
        status = false;
        ui->labelNameValid->show();
    }
    return status;
}

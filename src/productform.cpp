/*****************************************************************************
 * productform.cpp
 *
 * Created: 18/04/2014 by vijay
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
 * Vijay @ Dhanasekaran <vijay.kuruntham.gmail.com>
 *****************************************************************************/

#include "productform.h"
#include "ui_productform.h"
#include <QMessageBox>
#include "models/productsmodel.h"

ProductForm::ProductForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductForm)
{
    ui->setupUi(this);

    // Hide the errors labels at the start
    ui->labelCodeValid->hide();
    ui->labelMrpValid->hide();
    ui->labelNameValid->hide();
    ui->labelSalePriceValid->hide();
    ui->labelWholeSalePriceValid->hide();

    ui->comboBoxcategoryId->addItem("121");
    ui->comboBoxcategoryId->addItem("122");
    ui->comboBoxcategoryId->addItem("123");

    ui->comboBoxManufacturer->addItem("test1");
    ui->comboBoxManufacturer->addItem("test2");
    ui->comboBoxManufacturer->addItem("test3");

    ui->comboBoxUnit->addItem("100");
    ui->comboBoxUnit->addItem("101");
    ui->comboBoxUnit->addItem("102");

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));

    // Enter key to focus next control
    connect(ui->lineEditCode,SIGNAL(returnPressed()),ui->lineEditName,SLOT(setFocus()));
    connect(ui->lineEditName,SIGNAL(returnPressed()),ui->comboBoxcategoryId,SLOT(setFocus()));
    //connect(ui->comboBoxcategoryId->lineEdit(),SIGNAL(returnPressed()),ui->comboBoxManufacturer,SLOT(setFocus()));
    //connect(ui->comboBoxManufacturer->lineEdit(),SIGNAL(returnPressed()),ui->comboBoxUnit,SLOT(setFocus()));
    //connect(ui->comboBoxUnit->lineEdit(),SIGNAL(returnPressed()),ui->lineEditMrp,SLOT(setFocus()));
    connect(ui->lineEditMrp,SIGNAL(returnPressed()),ui->lineEditSalePrice,SLOT(setFocus()));
    connect(ui->lineEditSalePrice,SIGNAL(returnPressed()),ui->lineEditWholeSalePrice,SLOT(setFocus()));
    connect(ui->lineEditWholeSalePrice,SIGNAL(returnPressed()),ui->pushButtonSave,SLOT(setFocus()));

    connect(ui->lineEditCode,SIGNAL(editingFinished()),SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),SLOT(nameValid()));
    connect(ui->lineEditMrp,SIGNAL(editingFinished()),SLOT(mrpValid()));
    connect(ui->lineEditSalePrice,SIGNAL(editingFinished()),SLOT(salePriceValid()));
    connect(ui->lineEditWholeSalePrice,SIGNAL(editingFinished()),SLOT(wholeSalePriceValid()));
}

ProductForm::~ProductForm()
{
    delete ui;
}

//save the product form
void ProductForm::save()
{
    int valid = 0; // key for valid
    QString errors = ""; // string to display errors

    // message box initialization
    QMessageBox msgBox;
    msgBox.setText("Validation Error in this forms. Please correct the form and resubmit it");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // validate code field
    if(!ProductForm::codeValid())
    {
        valid =1;
        errors.append("\nThe Category Code field may be empty or contains text or greater than 10000");
    }

    // Validate Name field
    if(!ProductForm::nameValid())
    {
        valid = 1;
        errors.append("\nThe Name field may be empty or exceed the 20 characters limit");
    }

    //Validate Mrp field
    if(!ProductForm::mrpValid())
    {
        valid=1;
        errors.append("\nThe MRP field may be empty or contains text or greater than 10000");
    }

    //Validate Sale Price field
    if(!ProductForm::salePriceValid())
    {
        valid=1;
        errors.append("\nThe Sale Price field may be empty or contains text or greater than 10000");
    }

    //Validate Whole Sale Price field
    if(!ProductForm::wholeSalePriceValid())
    {
        valid=1;
        errors.append("\nThe Whole Sale Price field may be empty or contains text or greater than 10000");
    }

    // save the form if there is no errors
    if(valid==0)
    {
        int rowIndex = productsModel->rowCount();
        qDebug() << "rowIndex :::>" << rowIndex;
        productsModel->insertRow(rowIndex);
        productsModel->setData(productsModel->index(rowIndex,productsModel->fieldIndex("code")),ui->lineEditCode->text());
        productsModel->setData(productsModel->index(rowIndex,productsModel->fieldIndex("name")),ui->lineEditName->text());
        productsModel->setData(productsModel->index(rowIndex,productsModel->fieldIndex("createdDate")),"2014-04-22 00:00:00");
        productsModel->submit();

        clear();
        setCodeFocus();
    }

    // display the message box if there is any errors
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
}


/*void ProductForm::save()
{
    Product product;
    product.setCode(ui->lineEditCode->text());
    product.setName(ui->lineEditName->text());
    //QMessageBox::information(this,"title",ui->comboBoxcategoryId->property("currentText").toString());


    product.setCategoryId(ui->comboBoxcategoryId->property("currentText").toDouble(0));
    product.setManufacturer(ui->comboBoxManufacturer->property("currentText").toString());
    product.setUnit(ui->comboBoxUnit->property("currentText").toString());
    product.setMrp(ui->lineEditMrp->text().toDouble(0));
    product.setSprice(ui->lineEditSalePrice->text().toDouble());
    product.setWholeSalePrice(ui->lineEditWholeSalePrice->text().toDouble());

    bool status=product.save();
    qDebug()<<status;
    if(status==true)
        QMessageBox::information(this,"title","Product Saved succesfully");
    else
        QMessageBox::information(this,"title","<b>Product NOT Saved succesfully</b>");
    setCodeFocus();
}*/

void ProductForm::clear(){
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
}

void ProductForm::setCodeFocus(){
    ui->lineEditCode->setFocus();
}


void ProductForm::setModel(ProductsModel *model){
    productsModel = model;
}

// validate the code field
bool ProductForm::codeValid(){
    FormValidation formValidation;
    bool status = false;
    if(formValidation.intValid(ui->lineEditCode->text()))
    {
        ui->labelCodeValid->hide();
        status = true;
    }
    else
    {
        ui->labelCodeValid->show();
        status = false;
    }
    return status;
}

// validate the name field
bool ProductForm::nameValid(){
    FormValidation formValidation;
    bool status= false;
    if(formValidation.textValid(ui->lineEditName->text(),20))
    {
        ui->labelNameValid->hide();
        status= true;
    }
    else
    {
        ui->labelNameValid->show();
        status= false;
    }
    return status;
}

//validate the mrp field
bool ProductForm::mrpValid(){
    FormValidation formValidation;
    bool status = false;
    if(formValidation.intValid(ui->lineEditMrp->text()))
    {
        ui->labelMrpValid->hide();
        status = true;
    }
    else
    {
        ui->labelMrpValid->show();
        status = false;
    }
    return status;
}

//validate the sale price field
bool ProductForm::salePriceValid(){
    FormValidation formValidation;
    bool status = false;
    if(formValidation.intValid(ui->lineEditSalePrice->text()))
    {
        ui->labelSalePriceValid->hide();
        status = true;
    }
    else
    {
        ui->labelSalePriceValid->show();
        status = false;
    }
    return status;
}

//validate the whole sale price field
bool ProductForm::wholeSalePriceValid(){
    FormValidation formValidation;
    bool status = false;
    if(formValidation.intValid(ui->lineEditSalePrice->text()))
    {
        ui->labelWholeSalePriceValid->hide();
        status = true;
    }
    else
    {
        ui->labelWholeSalePriceValid->show();
        status = false;
    }
    return status;
}

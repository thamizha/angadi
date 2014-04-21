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
#include "models/product.h"

ProductForm::ProductForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductForm)
{
    ui->setupUi(this);
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
}

ProductForm::~ProductForm()
{
    delete ui;
}

void ProductForm::setCodeFocus()
{
    ui->lineEditCode->setFocus();
}

void ProductForm::save()
{
    Product product;
    product.setCode(ui->lineEditCode->text());
    product.setName(ui->lineEditName->text());
    //QMessageBox::information(this,"title",ui->comboBoxcategoryId->property("currentText").toString());


    /*product.setCategoryId(25);
    product.setManufacturer("Vijay");
    product.setUnit("72kg");
    product.setMrp(250);
    product.setSprice(300);
    product.setWholeSalePrice(350);*/


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
}

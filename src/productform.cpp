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
#include "models/productsmodel.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlRelationalDelegate>
#include <QSqlError>
#include <QSqlRecord>

ProductForm::ProductForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductForm)
{
    ui->setupUi(this);

    ui->pushButtonSave->setText("Update");
    ui->pushButtonCancel->setEnabled(false);

    // Hide the errors labels at the start
    ui->labelManufacturer->hide();
    ui->comboBoxManufacturer->hide();
    ui->labelCodeValid->hide();
    ui->labelMrpValid->hide();
    ui->labelNameValid->hide();
    ui->labelSalePriceValid->hide();
    ui->labelWholeSalePriceValid->hide();

    ui->comboBoxManufacturer->addItem("Manufacturer 1");
    ui->comboBoxManufacturer->addItem("Manufacturer 2");
    ui->comboBoxManufacturer->addItem("Manufacturer 3");

    ui->comboBoxUnit->addItem("Nos");
    ui->comboBoxUnit->addItem("Kgs");
    ui->comboBoxUnit->addItem("Bundles");

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));

    connect(ui->lineEditCode,SIGNAL(editingFinished()),SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),SLOT(nameValid()));
    connect(ui->lineEditMrp,SIGNAL(editingFinished()),SLOT(mrpValid()));
    connect(ui->lineEditSalePrice,SIGNAL(editingFinished()),SLOT(salePriceValid()));
    connect(ui->lineEditWholeSalePrice,SIGNAL(editingFinished()),SLOT(wholeSalePriceValid()));

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this));
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
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
    if(valid==0){
        bool status;

        if(this->ui->pushButtonSave->text() == "Save"){
            int row = productsModel->rowCount();
            productsModel->insertRows(row, 1);

            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("code")),ui->lineEditCode->text());
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("name")),ui->lineEditName->text());

            QSqlQueryModel model;
            QSqlQuery query;
            query.prepare("Select id from categories where name = :category_name");
            query.bindValue(":category_name", ui->comboBoxcategoryId->currentText());
            query.exec();
            model.setQuery(query);
            QSqlRecord record = model.record(0);
            int category_id = record.value("id").toInt();
            QModelIndex idx = productsModel->index(row,4);
            productsModel->setData(idx, category_id, Qt::EditRole);
//            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("manufacturer")),ui->comboBoxManufacturer->currentText());
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("unit")),ui->comboBoxUnit->currentText());
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("mrp")),ui->lineEditMrp->text());
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("sprice")),ui->lineEditSalePrice->text());
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("wholeSalePrice")),ui->lineEditWholeSalePrice->text());

            QDateTime datetime = QDateTime::currentDateTime();
            productsModel->setData(productsModel->index(row,productsModel->fieldIndex("createdDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));

            productsModel->submitAll();

            this->ui->pushButtonSave->setEnabled(true);
            this->ui->pushButtonSave->setText("Update");

        }else if(this->ui->pushButtonSave->text() == "Update"){
            status = dataMapper->submit();

            if(status == true){
                productsModel->submitAll();
            }
        }
        productsModel->select();
        dataMapper->toLast();
        ui->pushButtonAdd->setEnabled(true);
        ui->pushButtonCancel->setEnabled(false);
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
    dataMapper->setModel(productsModel);

    ui->comboBoxcategoryId->setModel(productsModel->relationModel(4));
    ui->comboBoxcategoryId->setModelColumn(productsModel->relationModel(4)->fieldIndex("name"));

    dataMapper->addMapping(ui->lineEditCode,productsModel->fieldIndex("code"));
    dataMapper->addMapping(ui->lineEditName,productsModel->fieldIndex("name"));
    dataMapper->addMapping(ui->comboBoxcategoryId, 4);
//    dataMapper->addMapping(ui->comboBoxManufacturer,productsModel->fieldIndex("manufacturer"));
    dataMapper->addMapping(ui->comboBoxUnit,productsModel->fieldIndex("unit"));
    dataMapper->addMapping(ui->lineEditMrp,productsModel->fieldIndex("mrp"));
    dataMapper->addMapping(ui->lineEditSalePrice,productsModel->fieldIndex("sprice"));
    dataMapper->addMapping(ui->lineEditWholeSalePrice,productsModel->fieldIndex("wholeSalePrice"));

    dataMapper->toFirst();

    if(productsModel->rowCount() <= 0){
        this->ui->pushButtonSave->setEnabled(false);
    }
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

void ProductForm::setMapperIndex(QModelIndex index)
{
    this->ui->pushButtonSave->setText("Update");
    dataMapper->setCurrentIndex(index.row());
}


void ProductForm::on_pushButtonAdd_clicked()
{
    ui->pushButtonSave->setText("Save");
    ui->pushButtonSave->setEnabled(true);
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonCancel->setEnabled(true);
    clear();
    setCodeFocus();
}

void ProductForm::on_pushButtonCancel_clicked()
{
    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonCancel->setEnabled(false);
    this->ui->pushButtonSave->setText("Update");
    dataMapper->toLast();
    if(productsModel->rowCount() <= 0){
        this->ui->pushButtonSave->setEnabled(false);
    }
}


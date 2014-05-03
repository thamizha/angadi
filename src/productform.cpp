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
 * Selvam <vjpselvam@gmail.com>
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
#include <QDoubleValidator>

ProductForm::ProductForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductForm)
{
    ui->setupUi(this);

    formValidation = new FormValidation;

    // Hide the errors labels at the start
    ui->labelManufacturer->hide();
    ui->comboBoxManufacturer->hide();

    ui->comboBoxManufacturer->addItem("Manufacturer 1");
    ui->comboBoxManufacturer->addItem("Manufacturer 2");
    ui->comboBoxManufacturer->addItem("Manufacturer 3");

    ui->comboBoxUnit->addItem("Nos");
    ui->comboBoxUnit->addItem("Kgs");
    ui->comboBoxUnit->addItem("Bundles");

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->lineEditName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditName,SIGNAL(returnPressed()),this,SLOT(setSignalFromProductForm()));

    connect(ui->lineEditCode,SIGNAL(editingFinished()),SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),SLOT(nameValid()));
    connect(ui->lineEditMrp,SIGNAL(editingFinished()),SLOT(mrpValid()));
    connect(ui->lineEditSalePrice,SIGNAL(editingFinished()),SLOT(salePriceValid()));
    connect(ui->lineEditWholeSalePrice,SIGNAL(editingFinished()),SLOT(wholeSalePriceValid()));

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this));
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setFieldMaxLength();
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
        errors.append("\nThe Category Code field may be empty or contains text or greater than 10000 or this code already exist");
    }

    // Validate Name field
    if(!ProductForm::nameValid())
    {
        valid = 1;
        errors.append("\nThe Name field may be empty or exceed the 20 characters limit or this name already exist");
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

        if(dataMapper->currentIndex() < 0){
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

//            this->ui->pushButtonSave->setEnabled(true);
//            this->ui->pushButtonDelete->setEnabled(true);
//            this->ui->pushButtonSave->setText("Update");

        }else{
            QDateTime datetime = QDateTime::currentDateTime();
            this->setProperty("modifiedDate", datetime);

            status = dataMapper->submit();

            if(status == true){
                productsModel->submitAll();
            }
        }
//        productsModel->select();
//        dataMapper->toLast();
//        //ui->pushButtonAdd->setEnabled(true);
//        ui->pushButtonCancel->setEnabled(false);
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

void ProductForm::clear(){
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    ui->lineEditWholeSalePrice->setProperty("validationError",false);
    ui->lineEditWholeSalePrice->setProperty("validationSuccess",true);
    ui->lineEditWholeSalePrice->setStyleSheet(styleSheet());
    uninstallEventFilter();
}

void ProductForm::setCodeFocus(){
    ui->lineEditCode->setFocus();
    ui->lineEditCode->selectAll();
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

//    dataMapper->toFirst();
    setCodeFocus();

    if(productsModel->rowCount() <= 0){
        this->ui->pushButtonSave->setEnabled(false);
    }
}

// validate the code field
bool ProductForm::codeValid(){
    bool status = false;
    ui->lineEditCode->installEventFilter(this);
    if(ui->lineEditCode->text()!=0)
    {
        if (uniqueValid(ui->lineEditCode->text(),"code")){
            ui->lineEditCode->setProperty("validationError",false);
            ui->lineEditCode->setProperty("validationSuccess",true);
            ui->lineEditCode->setStyleSheet(styleSheet());
            status = true;
        }
        else
        {
            ui->flashMsgUp->setText("This Product Code has been already taken. Please select some other code for this Product.");
            ui->lineEditCode->setProperty("validationError",true);
            ui->lineEditCode->setProperty("validationSuccess",false);
            ui->lineEditCode->setStyleSheet(styleSheet());
            status = false;
        }
    }
    else
    {
        ui->flashMsgUp->setText("Product Code is empty. Please select any code for this Product.");
        //ui->labelCodeValid->show();
        ui->lineEditCode->setProperty("validationError",true);
        ui->lineEditCode->setProperty("validationSuccess",false);
        ui->lineEditCode->setStyleSheet(styleSheet());
        status = false;
    }
    return status;
}

// validate the name field
bool ProductForm::nameValid(){
    bool status= false;
    ui->lineEditName->installEventFilter(this);
    if(ui->lineEditName->text().length() > 0){
        if(uniqueValid(ui->lineEditName->text(),"name")){
            ui->lineEditName->setProperty("validationError",false);
            ui->lineEditName->setProperty("validationSuccess",true);
            ui->lineEditName->setStyleSheet(styleSheet());
            status= true;
        }
        else
        {
            ui->flashMsgUp->setText("This Product Name has been already taken. Please select some other name for this Product.");
            ui->lineEditName->setProperty("validationError",true);
            ui->lineEditName->setProperty("validationSuccess",false);
            ui->lineEditName->setStyleSheet(styleSheet());
            status= false;
        }
    }
    else
    {
        ui->flashMsgUp->setText("Product Name is empty. Please select any name for this Product.");
        ui->lineEditName->setProperty("validationError",true);
        ui->lineEditName->setProperty("validationSuccess",false);
        ui->lineEditName->setStyleSheet(styleSheet());
        status= false;
    }
    return status;
}

//validate the mrp field
bool ProductForm::mrpValid(){
    bool status = false;
    ui->lineEditMrp->installEventFilter(this);
    if(ui->lineEditMrp->text().length() > 0){
        if(formValidation->isDouble(ui->lineEditMrp->text())){
            ui->lineEditMrp->setProperty("validationError",false);
            ui->lineEditMrp->setProperty("validationSuccess",true);
            ui->lineEditMrp->setStyleSheet(styleSheet());
            status = true;
        }else{
            ui->flashMsgUp->setText("Mrp is not a number. You have to fix some price for this Product in number.");
            ui->lineEditMrp->setProperty("validationError",true);
            ui->lineEditMrp->setProperty("validationSuccess",false);
            ui->lineEditMrp->setStyleSheet(styleSheet());
            status = false;
        }
    }else{
        ui->flashMsgUp->setText("Mrp field is empty. You have to fix some price for this Product.");
        ui->lineEditMrp->setProperty("validationError",true);
        ui->lineEditMrp->setProperty("validationSuccess",false);
        ui->lineEditMrp->setStyleSheet(styleSheet());
        status = false;
    }
    return status;
}

//validate the sale price field
bool ProductForm::salePriceValid(){
    bool status = false;
    ui->lineEditSalePrice->installEventFilter(this);
    if(ui->lineEditSalePrice->text().length() > 0){
        if(formValidation->isDouble(ui->lineEditSalePrice->text())){
            if(ui->lineEditSalePrice->text().toDouble() <= ui->lineEditMrp->text().toDouble()){
                ui->lineEditSalePrice->setProperty("validationError",false);
                ui->lineEditSalePrice->setProperty("validationSuccess",true);
                ui->lineEditSalePrice->setStyleSheet(styleSheet());
                status = true;
            }else{
                ui->flashMsgUp->setText("Sale Price is not a number. You have to fix price in number.");
                ui->lineEditSalePrice->setProperty("validationError",true);
                ui->lineEditSalePrice->setProperty("validationSuccess",false);
                ui->lineEditSalePrice->setStyleSheet(styleSheet());
                status = false;
            }
        }
    }else{
            ui->flashMsgUp->setText("Sale Price is empty. You have to fix some price for this Product.");
            ui->lineEditSalePrice->setProperty("validationError",true);
            ui->lineEditSalePrice->setProperty("validationSuccess",false);
            ui->lineEditSalePrice->setStyleSheet(styleSheet());
            status = false;
        }


    return status;
}

//validate the whole sale price field
bool ProductForm::wholeSalePriceValid(){
    bool status = false;
    ui->lineEditWholeSalePrice->installEventFilter(this);
    if(ui->lineEditWholeSalePrice->text() > 0){
        if(formValidation->isDouble(ui->lineEditWholeSalePrice->text())){
            if(ui->lineEditWholeSalePrice->text().toDouble() <= ui->lineEditSalePrice->text().toDouble()){
                ui->lineEditWholeSalePrice->setProperty("validationError",false);
                ui->lineEditWholeSalePrice->setProperty("validationSuccess",true);
                ui->lineEditWholeSalePrice->setStyleSheet(styleSheet());
                status = true;
            }else{
                ui->flashMsgUp->setText("Whole Sale Price is not a number. Please fix the price in number.");
                ui->lineEditWholeSalePrice->setProperty("validationError",true);
                ui->lineEditWholeSalePrice->setProperty("validationSuccess",false);
                ui->lineEditWholeSalePrice->setStyleSheet(styleSheet());
                status = false;
            }
        }else{
            ui->flashMsgUp->setText("Whole Sale Price is empty. Please fix the price in number.");
            ui->lineEditWholeSalePrice->setProperty("validationError",true);
            ui->lineEditWholeSalePrice->setProperty("validationSuccess",false);
            ui->lineEditWholeSalePrice->setStyleSheet(styleSheet());
            status = false;
        }
    }
    return status;
}

void ProductForm::setMapperIndex(QModelIndex index)
{
//    this->ui->pushButtonSave->setText("Update");
    dataMapper->setCurrentIndex(index.row());
    setAllValidationSuccess();
}

void ProductForm::on_pushButtonCancel_clicked()
{
    clear();
    setCodeFocus();
}

void ProductForm::on_pushButtonDelete_clicked()
{
    QSqlRecord record = productsModel->record(dataMapper->currentIndex());

    QDateTime datetime = QDateTime::currentDateTime();
    //qDebug() << record.value("status");
    QChar t_status = 'D';
    record.setValue("status", t_status);
    //qDebug() << record.value("status");
    record.setValue("modifiedDate", datetime);
    productsModel->setRecord(dataMapper->currentIndex(),record);
    if(productsModel->submit()){
        if(productsModel->submitAll()){
            qDebug() << "Success";
        }
    }
    else
        qDebug() << "No";
    productsModel->select();
    dataMapper->toNext();
}

void ProductForm::onNameChanged(QString str)
{
    emit signalName(str);
}

void ProductForm::setSignalFromProductForm()
{
    emit signalFromProductForm();
}

bool ProductForm::uniqueValid(QString text, QString field)
{
    bool status = false;
    QString id;
    QSqlRecord cRecord;
    if(ui->pushButtonSave->text()=="Save")
        id = "0";
    else{
        cRecord=productsModel->record(dataMapper->currentIndex());
        id = cRecord.value("id").toString();
    }
    int count = formValidation->uniqueValid(id,text,"products",field);
    if(count <= 0){
        status = true;
    }else{
        status = false;
    }
    return status;
}

bool ProductForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditCode)
    {
        if (event->type() == QEvent::FocusIn)
            ProductForm::codeValid();
        return false;
    }
    else if (obj == ui->lineEditMrp)
    {
        if (event->type() == QEvent::FocusIn)
            ProductForm::mrpValid();
        return false;
    }
    else if (obj == ui->lineEditName)
    {
        if (event->type() == QEvent::FocusIn)
            ProductForm::nameValid();
        return false;
    }
    else if (obj == ui->lineEditSalePrice)
    {
        if (event->type() == QEvent::FocusIn)
            ProductForm::salePriceValid();
        return false;
    }
    else if (obj == ui->lineEditWholeSalePrice)
    {
        if (event->type() == QEvent::FocusIn)
            ProductForm::wholeSalePriceValid();
        return false;
    }
    return ProductForm::eventFilter(obj, event);
}

void ProductForm::setFieldMaxLength()
{
    ui->lineEditCode->setMaxLength(100);
    ui->lineEditName->setMaxLength(200);

    ui->lineEditWholeSalePrice->setProperty("validationError",false);
    ui->lineEditWholeSalePrice->setProperty("validationSuccess",true);
    ui->lineEditWholeSalePrice->setStyleSheet(styleSheet());
}

void ProductForm::uninstallEventFilter()
{
    ui->lineEditCode->removeEventFilter(this);
    ui->lineEditMrp->removeEventFilter(this);
    ui->lineEditName->removeEventFilter(this);
    ui->lineEditSalePrice->removeEventFilter(this);
    ui->lineEditWholeSalePrice->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void ProductForm::setAllValidationSuccess()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",true);
        widget->setStyleSheet(styleSheet());
    }
}

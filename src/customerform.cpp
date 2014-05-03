/*****************************************************************************
 * customerform.cpp
 *
 * Created: 18/04/2014 by selvam
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
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "customerform.h"
#include "ui_customerform.h"

#include <QDateTime>
#include <QMessageBox>
#include <QPalette>

CustomerForm::CustomerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerForm)
{
    ui->setupUi(this);

    formValidation = new FormValidation;

    validCodeFlag = validNameFlag = 0;
    validEmailFlag = 1;

    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonSave->setEnabled(false);

    // populate customer type combo box
    ui->comboBoxType->addItem("Retailer");
    ui->comboBoxType->addItem("Whole Saler");

    // populate gender combo box
    ui->comboBoxGender->addItem("Male");
    ui->comboBoxGender->addItem("Female");
    ui->comboBoxGender->addItem("Transgender");

    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->lineEditName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditName,SIGNAL(returnPressed()),this,SLOT(setSignalFromCustomerForm()));

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setFieldMaxLength();

}

CustomerForm::~CustomerForm()
{
    delete ui;
}

void CustomerForm::setCodeFocus()
{
//    ui->lineEditCode->setFocus();
    ui->lineEditName->setFocus();
}

void CustomerForm::enableSave()
{
    if(validCodeFlag == 1 && validEmailFlag == 1 && validNameFlag == 1)
        ui->pushButtonSave->setEnabled(true);
    else
        ui->pushButtonSave->setEnabled(false);
}

void CustomerForm::save()
{
    bool status;

    if(this->ui->pushButtonSave->text() == "Save"){
        int row = customersModel->rowCount();
        customersModel->insertRows(row, 1);

        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("code")),ui->lineEditCode->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("name")),ui->lineEditName->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("type")),ui->comboBoxType->currentText());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("creditLimit")),ui->lineEditCreditLimit->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("contactPerson")),ui->lineEditContactPerson->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("address1")),ui->lineEditAddress1->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("address2")),ui->lineEditAddress2->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("city")),ui->lineEditCity->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("state")),ui->lineEditState->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("country")),ui->lineEditCountry->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("pincode")),ui->lineEditPincode->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("phone1")),ui->lineEditPhone1->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("phone2")),ui->lineEditPhone2->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("mobile1")),ui->lineEditMobile1->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("mobile2")),ui->lineEditMobile2->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("email")),ui->lineEditEmail->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("website")),ui->lineEditWebsite->text());
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("notes")),ui->textEditNote->toPlainText());

        QDateTime datetime = QDateTime::currentDateTime();
        customersModel->setData(customersModel->index(row,customersModel->fieldIndex("createdDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
        customersModel->submit();

        clear();

    }else if(this->ui->pushButtonSave->text() == "Update"){
        QDateTime datetime = QDateTime::currentDateTime();
        this->setProperty("modifiedDate", datetime);

        status = dataMapper->submit();
        if(status == true)
        {
            customersModel->submit();
        }
    }
    setCodeFocus();
}

void CustomerForm::setModel(CustomersModel *model){
    customersModel = model;
    dataMapper->setModel(customersModel);

    dataMapper->addMapping(ui->lineEditCode,customersModel->fieldIndex("code"));
    dataMapper->addMapping(ui->lineEditName,customersModel->fieldIndex("name"));

    dataMapper->addMapping(ui->comboBoxType,customersModel->fieldIndex("type"));
    dataMapper->addMapping(ui->lineEditCreditLimit,customersModel->fieldIndex("creditLimit"));
    dataMapper->addMapping(ui->lineEditContactPerson,customersModel->fieldIndex("contactPerson"));
    dataMapper->addMapping(ui->lineEditAddress1,customersModel->fieldIndex("address1"));
    dataMapper->addMapping(ui->lineEditAddress2,customersModel->fieldIndex("address2"));
    dataMapper->addMapping(ui->lineEditCity,customersModel->fieldIndex("city"));
    dataMapper->addMapping(ui->lineEditState,customersModel->fieldIndex("state"));
    dataMapper->addMapping(ui->lineEditCountry,customersModel->fieldIndex("country"));
    dataMapper->addMapping(ui->lineEditPincode,customersModel->fieldIndex("pincode"));
    dataMapper->addMapping(ui->lineEditPhone1,customersModel->fieldIndex("phone1"));
    dataMapper->addMapping(ui->lineEditPhone2,customersModel->fieldIndex("phone2"));
    dataMapper->addMapping(ui->lineEditMobile1,customersModel->fieldIndex("mobile1"));
    dataMapper->addMapping(ui->lineEditMobile2,customersModel->fieldIndex("mobile2"));
    dataMapper->addMapping(ui->lineEditEmail,customersModel->fieldIndex("email"));
    dataMapper->addMapping(ui->lineEditWebsite,customersModel->fieldIndex("website"));
    dataMapper->addMapping(ui->textEditNote,customersModel->fieldIndex("notes"));
    dataMapper->addMapping(this,customersModel->fieldIndex("modifiedDate"), "modifiedDate");
//    dataMapper->toFirst();

    setCodeFocus();

    if(customersModel->rowCount() <= 0){
        this->ui->pushButtonSave->setEnabled(false);
    }
}

void CustomerForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
    ui->textEditNote->clear();
    uninstallEventFilter();
}

void CustomerForm::setMapperIndex(QModelIndex index)
{
//    this->ui->pushButtonSave->setText("Update");
    dataMapper->setCurrentIndex(index.row());
    setAllValidationSuccess();
}

void CustomerForm::search(QString value)
{
    QString searchValue = "name = ";
    searchValue.append(value);
    customersModel->selectRow(1);
}

void CustomerForm::on_pushButtonCancel_clicked()
{
    ui->pushButtonDelete->setEnabled(true);

    if(this->ui->pushButtonSave->text() == "Save"){
        clear();

        this->ui->pushButtonSave->setText("Update");
        dataMapper->toLast();

    }else if(this->ui->pushButtonSave->text() == "Update"){
        dataMapper->setCurrentIndex(dataMapper->currentIndex());

    }
    setCodeFocus();
}

QDateTime CustomerForm::modifiedDate()
{
    return m_modifiedDate;
}

void CustomerForm::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

void CustomerForm::onNameChanged(QString str)
{
    emit signalName(str);
}

void CustomerForm::hideValidationErrors()
{

}

void CustomerForm::setSignalFromCustomerForm()
{
    emit signalFromCustomerForm();
}

bool CustomerForm::on_lineEditCode_editingFinished()
{
    bool status = false;
    ui->lineEditCode->installEventFilter(this);
    if(ui->lineEditCode->text()!=0)
    {
        if(uniqueValid(ui->lineEditCode->text(),"code"))
        {
            ui->lineEditCode->setProperty("validationError",false);
            ui->lineEditCode->setStyleSheet(styleSheet());
            //ui->labelCodeValid->hide();
            status = true;
            validCodeFlag = 1;
        }
        else
        {
            ui->flashMsgUp->setText("This Code has been already taken. Please select some other code.");
            ui->lineEditCode->setProperty("validationError",true);
            ui->lineEditCode->setStyleSheet(styleSheet());
            //ui->labelCodeValid->show();
            status = false;
            validCodeFlag = 0;
        }
    }
    else
    {
        ui->flashMsgUp->setText("Code is empty. Please give any code.");
        //ui->labelCodeValid->show();
        ui->lineEditCode->setProperty("validationError",true);
        ui->lineEditCode->setStyleSheet(styleSheet());
        status = false;
        validCodeFlag = 0;
    }
    enableSave();
    return status;
}

bool CustomerForm::on_lineEditName_editingFinished()
{
    bool status= false;
    ui->lineEditName->installEventFilter(this);
    if(ui->lineEditName->text()!=0)
    {
        if(uniqueValid(ui->lineEditName->text(),"name"))
        {
            ui->lineEditName->setProperty("validationError",false);
            ui->lineEditName->setStyleSheet(styleSheet());
            //ui->labelNameValid->hide();
            status= true;
            validNameFlag = 1;
        }
        else
        {
            ui->flashMsgUp->setText("This Name has been already taken. Please select some other name.");
            ui->lineEditName->setProperty("validationError",true);
            ui->lineEditName->setStyleSheet(styleSheet());
            //ui->labelNameValid->show();
            status= false;
            validNameFlag = 0;
        }
    }
    else
    {
        ui->flashMsgUp->setText("The Name is empty. Please select some name.");
        ui->lineEditName->setProperty("validationError",true);
        ui->lineEditName->setStyleSheet(styleSheet());
        //ui->labelNameValid->show();
        status= false;
        validNameFlag = 0;
    }
    enableSave();
    return status;
}

bool CustomerForm::uniqueValid(QString text, QString field)
{
    bool status = false;
    FormValidation formValidation;
    QString id;
    QSqlRecord cRecord;
    if(ui->pushButtonSave->text()=="Save")
        id = "0";
    else
    {
        cRecord=customersModel->record(dataMapper->currentIndex());
        id = cRecord.value("id").toString();
    }
    int count = formValidation.uniqueValid(id,text,"customers",field);
    if(count <= 0)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool CustomerForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditCode)
    {
        if (event->type() == QEvent::FocusIn)
            CustomerForm::on_lineEditCode_editingFinished();
        return false;
    }
    else if (obj == ui->lineEditName)
    {
        if (event->type() == QEvent::FocusIn)
            CustomerForm::on_lineEditName_editingFinished();
        return false;
    }
    else if (obj == ui->lineEditEmail)
    {
        if (event->type() == QEvent::FocusIn)
            CustomerForm::on_lineEditEmail_editingFinished();
        return false;
    }
    return CustomerForm::eventFilter(obj, event);
}

bool CustomerForm::on_lineEditEmail_editingFinished()
{
    bool status = false;
    ui->lineEditEmail->installEventFilter(this);
    if(ui->lineEditEmail->text() > 0){
        if(formValidation->emailValid(ui->lineEditEmail->text())){
            ui->lineEditEmail->setProperty("validationError",false);
            ui->lineEditEmail->setProperty("validationSuccess",true);
            ui->lineEditEmail->setStyleSheet(styleSheet());
            status = true;
            validEmailFlag = 1;
        }else{
            ui->flashMsgUp->setText("This is not a valid Email Address");
            ui->lineEditEmail->setProperty("validationError",true);
            ui->lineEditEmail->setProperty("validationSuccess",false);
            ui->lineEditEmail->setStyleSheet(styleSheet());
            status = false;
            validEmailFlag = 0;
        }
    }else{
        ui->lineEditEmail->setProperty("validationError",false);
        ui->lineEditEmail->setProperty("validationSuccess",true);
        ui->lineEditEmail->setStyleSheet(styleSheet());
        status = false;
        validEmailFlag = 1;
    }
    enableSave();
    return status;
}

void CustomerForm::uninstallEventFilter()
{
    ui->lineEditCode->removeEventFilter(this);
    ui->lineEditName->removeEventFilter(this);
    ui->lineEditEmail->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void CustomerForm::setFieldMaxLength()
{
    ui->lineEditCode->setMaxLength(100);
    ui->lineEditName->setMaxLength(200);
}

void CustomerForm::setAllValidationSuccess()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",true);
        widget->setStyleSheet(styleSheet());
    }
}

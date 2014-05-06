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

#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>

CustomerForm::CustomerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerForm)
{
    ui->setupUi(this);

    formValidation = new FormValidation;

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    validCodeFlag = validNameFlag = validCreditLimitFlag = validEmailFlag = 0;

    ui->pushButtonDelete->setEnabled(false);
//    ui->pushButtonSave->setEnabled(false);

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
    connect(ui->lineEditCode,SIGNAL(editingFinished()),this,SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),this,SLOT(nameValid()));
    connect(ui->lineEditCreditLimit,SIGNAL(editingFinished()),this,SLOT(creditLimitValid()));
    connect(ui->lineEditContactPerson,SIGNAL(editingFinished()),this,SLOT(contactPersonValid()));
    connect(ui->lineEditAddress1,SIGNAL(editingFinished()),this,SLOT(address1Valid()));
    connect(ui->lineEditAddress2,SIGNAL(editingFinished()),this,SLOT(address2Valid()));
    connect(ui->lineEditCity,SIGNAL(editingFinished()),this,SLOT(cityValid()));
    connect(ui->lineEditState,SIGNAL(editingFinished()),this,SLOT(stateValid()));
    connect(ui->lineEditCountry,SIGNAL(editingFinished()),this,SLOT(countryValid()));
    connect(ui->lineEditPincode,SIGNAL(editingFinished()),this,SLOT(pincodeValid()));
    connect(ui->lineEditPhone1,SIGNAL(editingFinished()),this,SLOT(phone1Valid()));
    connect(ui->lineEditPhone2,SIGNAL(editingFinished()),this,SLOT(phone2Valid()));
    connect(ui->lineEditMobile1,SIGNAL(editingFinished()),this,SLOT(mobile1Valid()));
    connect(ui->lineEditMobile2,SIGNAL(editingFinished()),this,SLOT(mobile2Valid()));
    connect(ui->lineEditWebsite,SIGNAL(editingFinished()),this,SLOT(WebsiteValid()));
    connect(ui->lineEditEmail,SIGNAL(editingFinished()),this,SLOT(emailValid()));

    setFieldMaxLength();

}

CustomerForm::~CustomerForm()
{
    delete ui;
}

bool CustomerForm::contactPersonValid()
{
    if(ui->lineEditContactPerson->text().length()>0){
        ui->lineEditContactPerson->setProperty("validationError",false);
        ui->lineEditContactPerson->setProperty("validationSuccess",true);
        ui->lineEditContactPerson->setStyleSheet(styleSheet());
    }
        return true;
}

bool CustomerForm::address1Valid()
{
    if(ui->lineEditAddress1->text().length()>0){
        ui->lineEditAddress1->setProperty("validationError",false);
        ui->lineEditAddress1->setProperty("validationSuccess",true);
        ui->lineEditAddress1->setStyleSheet(styleSheet());
    }
        return true;
}

bool CustomerForm::address2Valid()
{
    if(ui->lineEditAddress2->text().length()>0){
        ui->lineEditAddress2->setProperty("validationError",false);
        ui->lineEditAddress2->setProperty("validationSuccess",true);
        ui->lineEditAddress2->setStyleSheet(styleSheet());
    }
        return true;
}

bool CustomerForm::cityValid()
{
  if(ui->lineEditCity->text().length()>0){
    ui->lineEditCity->setProperty("validationError",false);
    ui->lineEditCity->setProperty("validationSuccess",true);
    ui->lineEditCity->setStyleSheet(styleSheet());\
  }
    return true;
}

bool CustomerForm::stateValid()
{
  if(ui->lineEditState->text().length()>0){
    ui->lineEditState->setProperty("validationError",false);
    ui->lineEditState->setProperty("validationSuccess",true);
    ui->lineEditState->setStyleSheet(styleSheet());\
  }
    return true;
}

bool CustomerForm::countryValid()
{
   if(ui->lineEditCountry->text().length()>0){
    ui->lineEditCountry->setProperty("validationError",false);
    ui->lineEditCountry->setProperty("validationSuccess",true);
    ui->lineEditCountry->setStyleSheet(styleSheet());\
   }
    return true;
}

bool CustomerForm::pincodeValid()
{
  if(ui->lineEditPincode->text().length()>0){
    ui->lineEditPincode->setProperty("validationError",false);
    ui->lineEditPincode->setProperty("validationSuccess",true);
    ui->lineEditPincode->setStyleSheet(styleSheet());\
  }
    return true;
}

bool CustomerForm::phone1Valid()
{
   if(ui->lineEditPhone1->text().length()>0){
    ui->lineEditPhone1->setProperty("validationError",false);
    ui->lineEditPhone1->setProperty("validationSuccess",true);
    ui->lineEditPhone1->setStyleSheet(styleSheet());\
   }
    return true;
}

bool CustomerForm::phone2Valid()
{
   if(ui->lineEditPhone2->text().length()>0){
    ui->lineEditPhone2->setProperty("validationError",false);
    ui->lineEditPhone2->setProperty("validationSuccess",true);
    ui->lineEditPhone2->setStyleSheet(styleSheet());\
   }
    return true;
}


bool CustomerForm::mobile1Valid()
{
   if(ui->lineEditMobile1->text().length()>0){
    ui->lineEditMobile1->setProperty("validationError",false);
    ui->lineEditMobile1->setProperty("validationSuccess",true);
    ui->lineEditMobile1->setStyleSheet(styleSheet());\
   }
    return true;
}

bool CustomerForm::mobile2Valid()
{
   if(ui->lineEditMobile2->text().length()>0){
    ui->lineEditMobile2->setProperty("validationError",false);
    ui->lineEditMobile2->setProperty("validationSuccess",true);
    ui->lineEditMobile2->setStyleSheet(styleSheet());\
   }
    return true;
}

bool CustomerForm::WebsiteValid()
{
   if(ui->lineEditWebsite->text().length()>0){
    ui->lineEditWebsite->setProperty("validationError",false);
    ui->lineEditWebsite->setProperty("validationSuccess",true);
    ui->lineEditWebsite->setStyleSheet(styleSheet());\
   }
    return true;
}

void CustomerForm::save()
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
    if(!CustomerForm::codeValid()){
        validError = 1;
        errors.append("\nThe Customer Code field may be empty or already exit");
    }

    // validate name field
    if(!CustomerForm::nameValid()){
        validError = 1;
        errors.append("\n\nThe Customer Name field may be empty or already exit");
    }

    // validate credit limit field
    if(!CustomerForm::creditLimitValid()){
        validError = 1;
        errors.append("\n\nThe Customer Credit Limit field may be empty or not a number");
    }

    // validate name field
    if(!CustomerForm::emailValid()){
        validError = 1;
        errors.append("\n\nThe Customer email field may be empty or invalid");
    }

    // save the form if there is no errors
    if(validError == 0){
        bool status = false;

        if(dataMapper->currentIndex() < 0){
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

            statusMsg = ui->lineEditName->text() + " saved successfully";
            emit signalStatusBar(statusMsg);

        }else{
            QDateTime datetime = QDateTime::currentDateTime();
            this->setProperty("modifiedDate", datetime);

            status = dataMapper->submit();
            if(status == true){
                customersModel->submit();
            }
            statusMsg = ui->lineEditName->text() + " updated successfully";
            emit signalStatusBar(statusMsg);
        }
        resetDataMapper();
        clear();
        setCodeFocus();
    }else{
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

void CustomerForm::setCodeFocus()
{
    ui->lineEditCode->setFocus();
    ui->lineEditCode->selectAll();
}

void CustomerForm::setNameFocus()
{
    ui->lineEditName->setFocus();
    ui->lineEditName->selectAll();
}

void CustomerForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    uninstallEventFilter();
    ui->pushButtonSave->setText("Save");
    ui->pushButtonDelete->setEnabled(false);
//    ui->pushButtonSave->setEnabled(false);
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

    setCodeFocus();
}

// function to validate code field
bool CustomerForm::codeValid(){
    bool status = false;
    QString flashMsg = "";
    ui->lineEditCode->installEventFilter(this);
    if(ui->lineEditCode->text().length() > 0){
        if(uniqueValid(ui->lineEditCode->text(), "code")){
            ui->lineEditCode->setProperty("validationError",false);
            ui->lineEditCode->setProperty("validationSuccess",true);
            ui->lineEditCode->setStyleSheet(styleSheet());
            validCodeFlag = 1;
            status = true;
        }else{
            flashMsg = "This Code has been already taken. Please give some other code.";
            ui->lineEditCode->setProperty("validationError",true);
            ui->lineEditCode->setProperty("validationSuccess",false);
            ui->lineEditCode->setStyleSheet(styleSheet());
            validCodeFlag = 0;
            status = false;
        }
    }else{
        flashMsg = "Code field is empty. Please give some values.";
        ui->lineEditCode->setProperty("validationError",true);
        ui->lineEditCode->setProperty("validationSuccess",false);
        ui->lineEditCode->setStyleSheet(styleSheet());
        validCodeFlag = 0;
        status = false;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

//function to validate name field
bool CustomerForm::nameValid(){
    bool status = false;
    QString flashMsg = "";
    ui->lineEditName->installEventFilter(this);
    if(ui->lineEditName->text().length() > 0){
        if(uniqueValid(ui->lineEditName->text(),"name")){
            status = true;
            ui->lineEditName->setProperty("validationError",false);
            ui->lineEditName->setProperty("validationSuccess",true);
            ui->lineEditName->setStyleSheet(styleSheet());
            validNameFlag = 1;
        }else{
            status = false;
            flashMsg = "This Name has been already taken. Please give some other name.";
            ui->lineEditName->setProperty("validationError",true);
            ui->lineEditName->setProperty("validationSuccess",false);
            ui->lineEditName->setStyleSheet(styleSheet());
            validNameFlag = 0;
        }
    }else{
        status = false;
        flashMsg = "Name field is empty. Please give some value.";
        ui->lineEditName->setProperty("validationError",true);
        ui->lineEditName->setProperty("validationSuccess",false);
        ui->lineEditName->setStyleSheet(styleSheet());
        validNameFlag = 0;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

bool CustomerForm::creditLimitValid()
{
    bool status = false;
    QString flashMsg = "";
    ui->lineEditCreditLimit->installEventFilter(this);
    if(ui->lineEditCreditLimit->text().length() > 0){
        if(formValidation->isDouble(ui->lineEditCreditLimit->text())){
            status = true;
            ui->lineEditCreditLimit->setProperty("validationError",false);
            ui->lineEditCreditLimit->setProperty("validationSuccess",true);
            ui->lineEditCreditLimit->setStyleSheet(styleSheet());
            validCreditLimitFlag = 1;
        }else{
            status = false;
            flashMsg = "Credit limit should be a number.";
            ui->lineEditCreditLimit->setProperty("validationError",true);
            ui->lineEditCreditLimit->setProperty("validationSuccess",false);
            ui->lineEditCreditLimit->setStyleSheet(styleSheet());
            validCreditLimitFlag = 0;
        }
    }else{
        status = false;
        flashMsg = "Credit limit field is empty. Please give some values.";
        ui->lineEditCreditLimit->setProperty("validationError",true);
        ui->lineEditCreditLimit->setProperty("validationSuccess",false);
        ui->lineEditCreditLimit->setStyleSheet(styleSheet());
        validCreditLimitFlag = 0;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

bool CustomerForm::uniqueValid(QString text,QString field)
{
    bool status = false;
    FormValidation formValidation;
    QString id;
    QSqlRecord cRecord;
    if(dataMapper->currentIndex() < 0){
        id = "0";

    }else{
        cRecord = customersModel->record(dataMapper->currentIndex());
        id = cRecord.value("id").toString();

    }
    int count = formValidation.uniqueValid(id, text, "customers", field);
    if(count <= 0){
        status = true;
    }else{
        status = false;
    }
    return status;
}

bool CustomerForm::emailValid()
{
    bool status = false;
    QString flashMsg = "";
    ui->lineEditEmail->installEventFilter(this);
    if(ui->lineEditEmail->text().length() > 0){
        if(formValidation->emailValid(ui->lineEditEmail->text())){
            ui->lineEditEmail->setProperty("validationError",false);
            ui->lineEditEmail->setProperty("validationSuccess",true);
            ui->lineEditEmail->setStyleSheet(styleSheet());
            status = true;
            validEmailFlag = 1;
        }else{
            flashMsg = "This is not a valid Email Address";
            ui->lineEditEmail->setProperty("validationError",true);
            ui->lineEditEmail->setProperty("validationSuccess",false);
            ui->lineEditEmail->setStyleSheet(styleSheet());
            status = false;
            validEmailFlag = 0;
        }
    }
    else{
//        ui->lineEditEmail->setProperty("validationError",false);
//        ui->lineEditEmail->setProperty("validationSuccess",true);
//        ui->lineEditEmail->setStyleSheet(styleSheet());
        status = true;
        validEmailFlag = 1;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

void CustomerForm::setMapperIndex(QModelIndex index)
{
    clear();
    dataMapper->setCurrentIndex(index.row());
    this->ui->pushButtonSave->setText("Update");
    ui->pushButtonDelete->setEnabled(true);
    validCodeFlag = validNameFlag = validCreditLimitFlag = validEmailFlag = 1;
//    ui->pushButtonSave->setEnabled(false);
//    setAllValidationSuccess();
}

void CustomerForm::search(QString value)
{
    QString searchValue = "code = ";
    searchValue.append(value);
    customersModel->selectRow(1);
}

void CustomerForm::on_pushButtonCancel_clicked()
{
    resetDataMapper();
    clear();
    setFieldMaxLength();
    setCodeFocus();
}

void CustomerForm::on_pushButtonDelete_clicked()
{
    QSqlRecord record = customersModel->record(dataMapper->currentIndex());
    statusMsg = ui->lineEditName->text() + " deleted successfully";

    QDateTime datetime = QDateTime::currentDateTime();
    QChar t_status = 'D';
    record.setValue("status", t_status);
    record.setValue("modifiedDate", datetime);
    customersModel->setRecord(dataMapper->currentIndex(), record);
    customersModel->submitAll();
    customersModel->select();

    emit signalStatusBar(statusMsg);

    on_pushButtonCancel_clicked();
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

void CustomerForm::setSignalFromCustomerForm()
{
    emit signalFromCustomerForm();
}

void CustomerForm::setFieldMaxLength()
{
    ui->lineEditCode->setMaxLength(100);
    ui->lineEditName->setMaxLength(200);
    ui->lineEditContactPerson->setMaxLength(200);
    ui->lineEditAddress1->setMaxLength(255);
    ui->lineEditAddress2->setMaxLength(255);
    ui->lineEditCity->setMaxLength(100);
    ui->lineEditState->setMaxLength(100);
    ui->lineEditCountry->setMaxLength(100);
    ui->lineEditPincode->setMaxLength(10);
    ui->lineEditPhone1->setMaxLength(20);
    ui->lineEditPhone2->setMaxLength(20);
    ui->lineEditMobile1->setMaxLength(20);
    ui->lineEditMobile2->setMaxLength(20);
    ui->lineEditEmail->setMaxLength(80);
    ui->lineEditWebsite->setMaxLength(80);

//    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
//        if(widget != ui->lineEditCode && widget != ui->lineEditName && widget != ui->lineEditCreditLimit){
//            widget->setProperty("validationError",false);
//            widget->setProperty("validationSuccess",false);
//            widget->setStyleSheet(styleSheet());
//        }
//    }
//    ui->textEditNote->setProperty("validationError",false);
//    ui->textEditNote->setProperty("validationSuccess",false);
//    ui->textEditNote->setStyleSheet(styleSheet());
}

void CustomerForm::resetDataMapper()
{
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    setModel(customersModel);
}

bool CustomerForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditCode){
        if (event->type() == QEvent::FocusIn)
            CustomerForm::codeValid();
        return false;
    }else if (obj == ui->lineEditName){
        if (event->type() == QEvent::FocusIn)
            CustomerForm::nameValid();
        return false;
    }else if (obj == ui->lineEditCreditLimit){
        if (event->type() == QEvent::FocusIn)
            CustomerForm::creditLimitValid();
        return false;
    }else if (obj == ui->lineEditEmail){
        if (event->type() == QEvent::FocusIn)
            CustomerForm::emailValid();
        return false;
    }
    return CustomerForm::eventFilter(obj, event);
}

void CustomerForm::uninstallEventFilter()
{
    ui->lineEditCode->removeEventFilter(this);
    ui->lineEditName->removeEventFilter(this);
    ui->lineEditCreditLimit->removeEventFilter(this);
    ui->lineEditEmail->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void CustomerForm::setAllValidationSuccess()
{
    validCodeFlag = validNameFlag = validCreditLimitFlag = validEmailFlag = 1;
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    ui->textEditNote->setProperty("validationError",false);
    ui->textEditNote->setProperty("validationSuccess",false);
    ui->textEditNote->setStyleSheet(styleSheet());
}

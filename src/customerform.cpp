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

CustomerForm::CustomerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerForm)
{
    ui->setupUi(this);

    // populate customer type combo box
    ui->comboBoxType->addItem("Retailer");
    ui->comboBoxType->addItem("Whole Saler");

    // populate gender combo box
    ui->comboBoxGender->addItem("Male");
    ui->comboBoxGender->addItem("Female");
    ui->comboBoxGender->addItem("Transgender");

    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(deleteAll()));
}

CustomerForm::~CustomerForm()
{
    delete ui;
}

void CustomerForm::setCodeFocus()
{
    ui->lineEditCode->setFocus();
}

void CustomerForm::save()
{
    Customer customer;
    customer.setCode(ui->lineEditCode->text());
    customer.setName(ui->lineEditName->text());
    customer.setType(ui->comboBoxType->currentText());
    customer.setCreditLimit(ui->lineEditCreditLimit->text().toDouble());
    customer.setContactPerson(ui->lineEditContactPerson->text());
    customer.setAddress1(ui->lineEditAddress1->text());
    customer.setAddress2(ui->lineEditAddress2->text());
    customer.setCity(ui->lineEditCity->text());
    customer.setState(ui->lineEditState->text());
    customer.setCountry(ui->lineEditCountry->text());
    customer.setPincode(ui->lineEditPincode->text());
    customer.setPhone1(ui->lineEditPhone1->text());
    customer.setPhone2(ui->lineEditPhone2->text());
    customer.setMobile1(ui->lineEditMobile1->text());
    customer.setMobile2(ui->lineEditMobile2->text());
    customer.setEmail(ui->lineEditEmail->text());
    customer.setWebsite(ui->lineEditWebsite->text());
    customer.setNotes(ui->textEditNote->toPlainText());
    bool status = customer.save();
    qDebug() << status;
}

void CustomerForm::deleteAll()
{
    Customer customer;
    customer.setCode("2");
    customer.deleteByCode();
}

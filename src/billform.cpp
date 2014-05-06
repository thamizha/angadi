/*****************************************************************************
 * productsmodel.cpp
 *
 * Created: 22/04/2014 by vijay
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
 * D.Mohan Raj <mohanraj.hunk@live.com>
 *****************************************************************************/

#include "billform.h"
#include "ui_billform.h"

BillForm::BillForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillForm)
{
    ui->setupUi(this);
    billDataMapper = new QDataWidgetMapper;
    billItemDataMapper = new QDataWidgetMapper;

    billDataMapper->setItemDelegate(new QSqlRelationalDelegate(this));
    billDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    billItemDataMapper->setItemDelegate(new QSqlRelationalDelegate(this));
    billItemDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(save()));
}

BillForm::~BillForm()
{
    delete ui;
}

void BillForm::clear()
{

}

void BillForm::setCodeFocus()
{
    ui->lineEditCustomerCode->setFocus();
}

void BillForm::setModel(BillModel *billModel, BillItemModel *billItemModel)
{
    billModel = billModel;
    billItemModel = billItemModel;

    billDataMapper->setModel(billModel);
    billItemDataMapper->setModel(billItemModel);

    billDataMapper->addMapping(ui->lineEditInvoiceDate,billModel->fieldIndex("date"));
    billDataMapper->addMapping(ui->lineEditInvoiceNo,billModel->fieldIndex("id"));
    billDataMapper->addMapping(ui->lineEditTotal,billModel->fieldIndex("actualAmount"));
    billDataMapper->addMapping(ui->lineEditDiscount,billModel->fieldIndex("discount"));
    billDataMapper->addMapping(ui->lineEditTooBePaid,billModel->fieldIndex("totalAmount"));

    billItemDataMapper->addMapping(ui->lineEditProductName,billItemModel->relationModel(3));
    billItemDataMapper->addMapping(ui->lineEditUnit,billItemModel->fieldIndex("unit_price"));
    billItemDataMapper->addMapping(ui->lineEditQty,billItemModel->fieldIndex("quantity"));
    billItemDataMapper->addMapping(ui->lineEditTotal,billItemModel->fieldIndex("total"));

    setCodeFocus();
}

void BillForm::save(){

}

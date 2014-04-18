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

    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(save()));
}

CustomerForm::~CustomerForm()
{
    delete ui;
}

void CustomerForm::save()
{
    Customer customer;
    customer.setCode(ui->lineEditCode->text());
    customer.setName(ui->lineEditName->text());

    customer.save();
}

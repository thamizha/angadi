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

CategoryForm::CategoryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryForm)
{
    ui->setupUi(this);
    ui->pushButtonSave->setEnabled(false);
    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));

    // Enter key to focus next control
    connect(ui->lineEditCode,SIGNAL(returnPressed()),ui->lineEditName,SLOT(setFocus()));
    connect(ui->lineEditName,SIGNAL(returnPressed()),ui->pushButtonSave,SLOT(setFocus()));
	
    connect(ui->lineEditCode,SIGNAL(textChanged(QString)),this,SLOT(enableSave(QString)));
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

void CategoryForm::save()
{
    int rowIndex = categoriesModel->rowCount();
    qDebug() << "rowIndex :::>" << rowIndex;
    categoriesModel->insertRow(rowIndex);
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("code")),ui->lineEditCode->text());
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("name")),ui->lineEditName->text());
    categoriesModel->setData(categoriesModel->index(rowIndex,categoriesModel->fieldIndex("createdDate")),"2014-04-22 00:00:00");
    categoriesModel->submit();

    clear();
    setCodeFocus();
}

void CategoryForm::enableSave(QString value)
{
    int pos=0;
    QIntValidator v(1,100,this);
    qint8 vState= v.validate(value,pos);
    if(vState==2)
        ui->pushButtonSave->setEnabled(true);
    else
        ui->pushButtonSave->setEnabled(false);
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
}

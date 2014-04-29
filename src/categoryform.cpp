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
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "categoryform.h"
#include "ui_categoryform.h"
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>

CategoryForm::CategoryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryForm)
{
    ui->setupUi(this);

    ui->pushButtonSave->setText("Update");

    ui->labelCodeValid->hide();
    ui->labelNameValid->hide();

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->lineEditName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // Enter key to focus next control
    /*connect(ui->lineEditCode,SIGNAL(returnPressed()),ui->lineEditName,SLOT(setFocus()));
    connect(ui->lineEditName,SIGNAL(returnPressed()),ui->pushButtonSave,SLOT(setFocus()));*/
    connect(ui->lineEditCode,SIGNAL(editingFinished()),this,SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),this,SLOT(nameValid()));
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

void CategoryForm::save()
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
    if(!CategoryForm::codeValid())
    {
        validError=1;
        errors.append("\nThe Category Code field may be empty or contains text or greater than 10000");
    }

    // validate name field
    if(!CategoryForm::nameValid())
    {
        validError=1;
        errors.append("\n\nThe Category Name field may be empty or exceeds the limit 20 characters");
    }

    // save the form if there is no errors
    if(validError==0){
        bool status;

        if(this->ui->pushButtonSave->text() == "Save"){
            int row = categoriesModel->rowCount();
            categoriesModel->insertRows(row, 1);

            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("code")),ui->lineEditCode->text());
            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("name")),ui->lineEditName->text());

            QDateTime datetime = QDateTime::currentDateTime();
            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("createdDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
            categoriesModel->submit();

            //clear();
            this->ui->pushButtonSave->setEnabled(true);
            this->ui->pushButtonSave->setText("Update");

            categoriesModel->select();
            dataMapper->toLast();

        }else if(this->ui->pushButtonSave->text() == "Update"){
            int cIndex = dataMapper->currentIndex();

            QDateTime datetime = QDateTime::currentDateTime();
            this->setProperty("modifiedDate", datetime);

            status = dataMapper->submit();
            if(status == true)
            {
                categoriesModel->submit();
            }
            categoriesModel->select();
            dataMapper->setCurrentIndex(cIndex);
        }
        setCodeFocus();

    }else{                                      // display the error message if there is any errors
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

void CategoryForm::setCodeFocus()
{
    ui->lineEditCode->styleSheet().append("background-color: rgb(95, 164, 209);");
//    ui->lineEditCode->setFocus();
    ui->lineEditName->setFocus();
}

void CategoryForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
}

void CategoryForm::setModel(CategoriesModel *model){
    categoriesModel = model;
    dataMapper->setModel(categoriesModel);

    dataMapper->addMapping(ui->lineEditCode,categoriesModel->fieldIndex("code"));
    dataMapper->addMapping(ui->lineEditName,categoriesModel->fieldIndex("name"));
    dataMapper->addMapping(this,categoriesModel->fieldIndex("modifiedDate"), "modifiedDate");
//    dataMapper->toFirst();

    setCodeFocus();

    if(categoriesModel->rowCount() <= 0){
        this->ui->pushButtonSave->setEnabled(false);
    }
}

// function to validate code field
bool CategoryForm::codeValid(){
    bool status =false;
    FormValidation formValidation;
    if(formValidation.intValid(ui->lineEditCode->text()))
    {
        if(uniqueValid(ui->lineEditCode->text(),"code"))
        {
            ui->labelCodeValid->hide();
            status = true;
        }
        else
        {
            ui->labelCodeValid->show();
            status= false;
        }

    }
    else
    {
        ui->labelCodeValid->show();
        status= false;
    }
    return status;
}

//function to validate name field
bool CategoryForm::nameValid(){
    bool status = false;
    FormValidation formValidation;
    if(formValidation.textValid(ui->lineEditName->text(),20))
    {
        if(uniqueValid(ui->lineEditName->text(),"name"))
        {
            status = true;
            ui->labelNameValid->hide();
        }
        else
        {
            status = false;
            ui->labelNameValid->show();
        }
    }
    else
    {
        status = false;
        ui->labelNameValid->show();
    }
    return status;
}

void CategoryForm::setMapperIndex(QModelIndex index)
{
    this->ui->pushButtonSave->setText("Update");
    dataMapper->setCurrentIndex(index.row());
}

void CategoryForm::search(QString value)
{
    QString searchValue = "code = ";
    searchValue.append(value);
    categoriesModel->selectRow(1);
    qDebug() << categoriesModel->selectRow(1);
    //categoriesModel->setFilter(searchValue);
}

void CategoryForm::on_pushButtonAdd_clicked()
{
    this->ui->pushButtonSave->setText("Save");

    this->ui->pushButtonSave->setEnabled(true);

    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);

    clear();
    setCodeFocus();
}

void CategoryForm::on_pushButtonCancel_clicked()
{
    ui->pushButtonAdd->setEnabled(true);
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

void CategoryForm::on_pushButtonDelete_clicked()
{
    QSqlRecord record = categoriesModel->record(dataMapper->currentIndex());

    QSqlQueryModel model;
    QSqlQuery query;
    query.prepare("Select * from products where category_id = :category_id");
    query.bindValue(":category_id", record.value("id").toInt());
    query.exec();
    model.setQuery(query);

    if(model.rowCount() == 0){
        QDateTime datetime = QDateTime::currentDateTime();

        record.setValue("status", "D");
        record.setValue("modifiedDate", datetime);
        categoriesModel->setRecord(dataMapper->currentIndex(), record);
        categoriesModel->submit();

        categoriesModel->select();
        dataMapper->toNext();

        if(categoriesModel->rowCount() <= 0){
            clear();
            this->ui->pushButtonSave->setEnabled(false);
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText("Products found under this category. Cannot delete!!!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

QDateTime CategoryForm::modifiedDate() const
{
    return m_modifiedDate;
}

void CategoryForm::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

void CategoryForm::onNameChanged(QString str)
{
    emit signalName(str);
}

bool CategoryForm::uniqueValid(QString text,QString field)
{
    bool status = false;
    FormValidation formValidation;
    int count = formValidation.uniqueValid(0,text,"categories",field);
    if(ui->pushButtonSave->text()=="Save")
    {
        if(count == 0)
        {
            status = true;
        }
        else
        {
            status = false;
        }
    }
    else if (ui->pushButtonSave->text()=="Update")
    {
        if(count > 0)
        {
            status = true;
        }
        else
        {
            status = false;
        }
    }
    return status;
}

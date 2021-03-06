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
 * D.Mohan Raj <mohanraj.hunk@live.com>
 *****************************************************************************/

#include "categoryform.h"
#include "ui_categoryform.h"

#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QEvent>
#include <QTranslator>
#include <QSettings>
CategoryForm::CategoryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryForm)
{
    ui->setupUi(this);

    formValidation = new FormValidation;
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    validCodeFlag = validNameFlag = 0;

    ui->pushButtonDelete->setEnabled(false);
//    ui->pushButtonSave->setEnabled(false);

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->lineEditName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditName,SIGNAL(returnPressed()),this,SLOT(setSignalFromCategoryForm()));
    connect(ui->lineEditCode,SIGNAL(editingFinished()),this,SLOT(codeValid()));
    connect(ui->lineEditName,SIGNAL(editingFinished()),this,SLOT(nameValid()));

    connect(ui->lineEditCode,SIGNAL(returnPressed()),this,SLOT(categoryCodeSearch()));

    setFieldMaxLength();
    setLanguage();
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

void CategoryForm::settranslate()
{
    ui->retranslateUi(this);
}

void CategoryForm::setSaveButtonText(qint8 flag)         //flag = 0 for "save" else "update"
{
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::IniFormat);
    QString content = settings.value("s_language","").toString();

    if(content == "tamil_language"){                               //tab language settings
        QTranslator translator;
        translator.load("tamilLanguage_la");
        QApplication::instance()->installTranslator(&translator);
        if(flag == 0)
            ui->pushButtonSave->setText(CategoryForm::tr("Save"));
        else
            ui->pushButtonSave->setText(CategoryForm::tr("Update"));
    }
    else{
        if(flag == 0)
            ui->pushButtonSave->setText("Save");
        else
            ui->pushButtonSave->setText("Update");
    }
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
    if(!CategoryForm::codeValid()){
        validError = 1;
        errors.append("\nThe Category Code field may be empty or already exit");
    }

    // validate name field
    if(!CategoryForm::nameValid()){
        validError = 1;
        errors.append("\n\nThe Category Name field may be empty or already exit");
    }

    // save the form if there is no errors
    if(validError == 0){
        bool status;

        if(dataMapper->currentIndex() < 0){
            int row = categoriesModel->rowCount();
            categoriesModel->insertRows(row, 1);

            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("code")),ui->lineEditCode->text());
            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("name")),ui->lineEditName->text());

            QDateTime datetime = QDateTime::currentDateTime();
            categoriesModel->setData(categoriesModel->index(row,categoriesModel->fieldIndex("createdDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
            categoriesModel->submit();
            statusMsg = ui->lineEditName->text() + " saved successfully";
            emit signalStatusBar(statusMsg);
        }else{
            QDateTime datetime = QDateTime::currentDateTime();
            this->setProperty("modifiedDate", datetime);

            status = dataMapper->submit();
            if(status == true)
            {
                categoriesModel->submit();
                statusMsg = ui->lineEditName->text() + " updated successfully";
                emit signalStatusBar(statusMsg);
            }
        }
        emit signalUpdated();
        resetDataMapper();
        clear();
        setCodeFocus();
    }
    else{                                      // display the error message if there is any errors
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
    ui->lineEditCode->setFocus();
    ui->lineEditCode->selectAll();
}

void CategoryForm::setNameFocus()
{
    ui->lineEditName->setFocus();
    ui->lineEditName->selectAll();
}

void CategoryForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    uninstallEventFilter();
    setSaveButtonText(0);
//    ui->pushButtonSave->setText("Save");
    ui->pushButtonDelete->setEnabled(false);
    //ui->pushButtonSave->setEnabled(false);
}

void CategoryForm::setModel(CategoriesModel *model){
    model->select();
    categoriesModel = model;
    dataMapper->setModel(categoriesModel);

    dataMapper->addMapping(ui->lineEditCode,categoriesModel->fieldIndex("code"));
    dataMapper->addMapping(ui->lineEditName,categoriesModel->fieldIndex("name"));
    dataMapper->addMapping(this,categoriesModel->fieldIndex("modifiedDate"), "modifiedDate");
    setCodeFocus();
}

// function to validate code field
bool CategoryForm::codeValid(){
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
bool CategoryForm::nameValid(){
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
        flashMsg = "Name field is empty. Please give some values.";
        ui->lineEditName->setProperty("validationError",true);
        ui->lineEditName->setProperty("validationSuccess",false);
        ui->lineEditName->setStyleSheet(styleSheet());
        validNameFlag = 0;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

bool CategoryForm::uniqueValid(QString text,QString field)
{
    bool status = false;
    FormValidation formValidation;
    QString id;
    QSqlRecord cRecord;
    if(dataMapper->currentIndex() < 0){
        id = "0";

    }else{
        cRecord = categoriesModel->record(dataMapper->currentIndex());
        id = cRecord.value("id").toString();

    }
    int count = formValidation.uniqueValid(id, text, "categories", field);
    if(count <= 0){
        status = true;
    }else{
        status = false;
    }
    return status;
}

void CategoryForm::setMapperIndex(QModelIndex index)
{
    clear();
    dataMapper->setCurrentIndex(index.row());
    setSaveButtonText(1);
//    this->ui->pushButtonSave->setText("Update");
    ui->pushButtonDelete->setEnabled(true);
    validCodeFlag = validNameFlag = 1;
//    ui->pushButtonSave->setEnabled(false);
//    setAllValidationSuccess();
}

void CategoryForm::search(QString value)
{
    QString searchValue = "code = ";
    searchValue.append(value);
    categoriesModel->selectRow(1);
}

void CategoryForm::on_pushButtonCancel_clicked()
{
    resetDataMapper();
    clear();
    setCodeFocus();
}

void CategoryForm::on_pushButtonDelete_clicked()
{
    QMessageBox msgBox;

    QSqlRecord record = categoriesModel->record(dataMapper->currentIndex());

    QSqlQueryModel model;
    QSqlQuery query;
    query.prepare("Select * from products where category_id = :category_id and status = 'A'");
    query.bindValue(":category_id", record.value("id").toInt());
    query.exec();
    model.setQuery(query);

    if(model.rowCount() == 0){
        QDateTime datetime = QDateTime::currentDateTime();

        setLanguage();
        settings = new Settings;
        msgBox.setWindowTitle(settings->getCompanyName());
        QString msg = CategoryForm::tr("Are you sure you want to delete this category?");
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Ok);
        QPixmap pix(":/images/icons/delete.png");
        msgBox.setIconPixmap(pix);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Yes:
                statusMsg = ui->lineEditName->text() + CategoryForm::tr(" deleted successfully");

                record.setValue("status", "D");
                record.setValue("modifiedDate", datetime);
                categoriesModel->setRecord(dataMapper->currentIndex(), record);
                categoriesModel->submit();
                categoriesModel->select();

                emit signalUpdated();
                on_pushButtonCancel_clicked();
                break;
            default:
                // should never be reached
                break;
         }
    }else{
        msgBox.setText("Products found under this category. Cannot delete!!!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    emit signalStatusBar(statusMsg);
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

void CategoryForm::setSignalFromCategoryForm()
{
    emit signalFromCategoryForm();
}

void CategoryForm::setFieldMaxLength()
{
    ui->lineEditCode->setMaxLength(100);
    ui->lineEditName->setMaxLength(200);
}

void CategoryForm::resetDataMapper()
{
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    setModel(categoriesModel);
}

bool CategoryForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditCode){
        if(event->type() == QEvent::FocusIn)
            CategoryForm::codeValid();
        return false;
    }else if (obj == ui->lineEditName){
        if(event->type() == QEvent::FocusIn)
            CategoryForm::nameValid();
        return false;
    }
    return CategoryForm::eventFilter(obj, event);
}

void CategoryForm::uninstallEventFilter()
{
    ui->lineEditCode->removeEventFilter(this);
    ui->lineEditName->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void CategoryForm::setAllValidationSuccess()
{
    validCodeFlag = 1;
    validNameFlag = 1;
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",true);
        widget->setStyleSheet(styleSheet());
    }
}

void CategoryForm::setLanguage()
{
    //Language setup
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::IniFormat);
    QString content = settings.value("s_language","").toString();

    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);

     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void CategoryForm::categoryCodeSearch()
{
    QSqlRecord record;
    QModelIndex index;
    int flag = 0;
    for(int i=0; i<categoriesModel->rowCount()&&flag==0; i++){
        record = categoriesModel->record(i);
        if(record.value("code")== ui->lineEditCode->text()){
            index = categoriesModel->index(i,0);
            setMapperIndex(index);
            flag =1;
        }
    }
}

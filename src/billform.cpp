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
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "billform.h"
#include "ui_billform.h"
#include "timeeditdelegate.h"

#include <QSqlError>

#include <QTranslator>
#include <QApplication>
#include <QSettings>
#include <QDate>

BillForm::BillForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillForm)
{
    ui->setupUi(this);

    modelFlag = 0;

    ui->lineEditAvailable->setEnabled(false);
    ui->lineEditBalance->setEnabled(false);
    ui->lineEditChange->setEnabled(false);
    ui->lineEditGrandTotal->setEnabled(false);
    ui->lineEditLimit->setEnabled(false);
    ui->lineEditRate->setEnabled(false);
    ui->lineEditRoundOff->setEnabled(false);
    ui->lineEditTooBePaid->setEnabled(false);
    ui->lineEditTotal->setEnabled(false);
    ui->lineEditUnit->setEnabled(false);
    ui->lineEditUsed->setEnabled(false);

    formValidation = new FormValidation;
    billDataMapper = new QDataWidgetMapper;
    billDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    transactionModel = new QSqlTableModel;
    transactionModel->setTable("transactions");
    transactionModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    transactionModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Paid Date"));
    transactionModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Paid Amount"));

    billItemDataMapper = new QDataWidgetMapper;
    billItemDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    productDataMapper = new QDataWidgetMapper;
    productDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    customerDataMapper = new QDataWidgetMapper;
    customerDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ui->tableViewProductList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewProductList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableViewProductList->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewProductList->verticalHeader()->setVisible(true);
    ui->tableViewProductList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewProductList->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewCustomerBalance->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewCustomerBalance->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tableViewCustomerBalance->verticalHeader()->setVisible(false);
    ui->tableViewCustomerBalance->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCustomerBalance->setSelectionMode(QAbstractItemView::SingleSelection);

    validInvoiceNoFlag = 0;

    connect(ui->pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->lineEditCustomerName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditCustomerName,SIGNAL(returnPressed()),this,SLOT(setSignalFromBillForm()));

    connect(ui->lineEditProductName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(ui->lineEditProductName,SIGNAL(returnPressed()),this,SLOT(setSignalFromBillForm()));

    connect(ui->lineEditQty,SIGNAL(textChanged(QString)),this,SLOT(setProductTotal()));
    connect(ui->lineEditQty,SIGNAL(returnPressed()),this,SLOT(addProductItem()));

    connect(ui->lineEditGiven,SIGNAL(returnPressed()),this,SLOT(addTransaction()));

    connect(ui->lineEditTax,SIGNAL(textEdited(QString)),this,SLOT(updateToBeGiven()));
    connect(ui->lineEditDiscount,SIGNAL(textEdited(QString)),this,SLOT(updateToBeGiven()));
    connect(ui->lineEditTax,SIGNAL(textEdited(QString)),this,SLOT(updateToBeGiven()));
    connect(ui->lineEditGiven,SIGNAL(textEdited(QString)),this,SLOT(updateToBeGiven()));

    connect(ui->tableViewProductList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(productUpdate(QModelIndex)));
    connect(ui->tableViewProductList,SIGNAL(activated(QModelIndex)),this,SLOT(productUpdate(QModelIndex)));

    connect(ui->lineEditInvoiceNo,SIGNAL(editingFinished()),this,SLOT(invoiceNoValid()));
    connect(ui->lineEditCustomerCode,SIGNAL(textChanged(QString)),this,SLOT(customerCodeValid()));
    connect(ui->lineEditCustomerCode,SIGNAL(editingFinished()),this,SLOT(customerCodeValid()));
    connect(ui->lineEditCustomerName,SIGNAL(editingFinished()),this,SLOT(customerNameValid()));

    connect(ui->lineEditProductCode,SIGNAL(editingFinished()),this,SLOT(productCodeValid()));
    connect(ui->lineEditProductName,SIGNAL(editingFinished()),this,SLOT(productNameValid()));

    generateInvoiceNumber();
    setLanguage();
}

BillForm::~BillForm()
{
    delete ui;
}


void BillForm::settranslate()
{
    ui->retranslateUi(this);
}

void BillForm::setSaveButtonText(qint8 flag)         //flag = 0 for "save" else "update"
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
            ui->pushButtonSave->setText(BillForm::tr("Save"));
        else
            ui->pushButtonSave->setText(BillForm::tr("Update"));
    }
    else{
        if(flag == 0)
            ui->pushButtonSave->setText("Save");
        else
            ui->pushButtonSave->setText("Update");
    }
}



void BillForm::save(){
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime invoiceDateTime = ui->dateEditInvoiceDate->dateTime();
    int row, validError = 0;
    QString errors = "";

    // Initialization of message box
    QMessageBox msgBox;
    msgBox.setText("Validation Error in this forms. Please correct the form and resubmit it");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // validate code field
    if(!invoiceNoValid()){
        validError = 1;
        errors.append("\nThe Invoice No may be empty or already exit");
    }

    // validate code field
    if(ui->lineEditCustomerName->text().length() < 1){
        validError = 1;
        errors.append("\nThe Customer Name may be empty");
    }

    if(billItemModel->rowCount() < 1){
        validError = 1;
        errors.append("\n There are no products added for this bill. The product list seems to be empty.");
    }

    if(validError == 0){
        calBalance();
        if(billDataMapper->currentIndex() < 0){
            billModel->select();
            row = billModel->rowCount();
            billModel->insertRows(row, 1);
            billModel->setData(billModel->index(row,billModel->fieldIndex("createdDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
        }else{
            row = billDataMapper->currentIndex();
            billModel->setData(billModel->index(row,billModel->fieldIndex("modifiedDate")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
        }
        billModel->setData(billModel->index(row,billModel->fieldIndex("invoiceNo")),ui->lineEditInvoiceNo->text());
        billModel->setData(billModel->index(row,billModel->fieldIndex("invoiceDate")),invoiceDateTime.toString("yyyy-MM-dd hh:mm:ss"));

        QSqlQuery customerQuery;
        int customer_id;
        customerQuery.prepare("Select id from customers where name = :customer_name");
        customerQuery.bindValue(":customer_name", ui->lineEditCustomerName->text());
        customerQuery.exec();
        while(customerQuery.next())
            customer_id = customerQuery.value(0).toInt();
        QModelIndex idx = billModel->index(row,3);
        billModel->setData(idx, customer_id, Qt::EditRole);
        billModel->setData(billModel->index(row,billModel->fieldIndex("actualAmount")),ui->lineEditGrandTotal->text());
        billModel->setData(billModel->index(row,billModel->fieldIndex("discount")),ui->lineEditDiscount->text());
        billModel->setData(billModel->index(row,billModel->fieldIndex("totalAmount")),ui->lineEditTooBePaid->text());

        if(ui->lineEditBalance->text().toInt() == 0)
            billModel->setData(billModel->index(row,billModel->fieldIndex("paidStatus")),"P");
        else
            billModel->setData(billModel->index(row,billModel->fieldIndex("paidStatus")),"U");
        if(ui->lineEditBalance->text().length() == 0){
            billModel->setData(billModel->index(row,billModel->fieldIndex("dueAmount")),ui->lineEditTooBePaid->text());
            billModel->setData(billModel->index(row,billModel->fieldIndex("paidStatus")),"U");
        }else
            billModel->setData(billModel->index(row,billModel->fieldIndex("dueAmount")),ui->lineEditBalance->text());
        billModel->setData(billModel->index(row,billModel->fieldIndex("status")),"A");
        bool billStatus = billModel->submitAll();
        if(billStatus){
            QString productName;
            QSqlQuery itemQuery;
            QSqlRecord itemRecord;
            QSqlRecord billrecord = billModel->record(row);
            int bill_id = billrecord.value("id").toInt();
            for (int i = 0; i < billItemModel->rowCount(); ++i) {
                itemRecord = billItemModel->record(i);

                productName = itemRecord.value("product_id").toString();
                itemQuery.prepare("Select id from products where name = :product_name");
                itemQuery.bindValue(":product_name", productName);
                itemQuery.exec();
                itemQuery.value(0);
                while(itemQuery.next())
                    productName = itemQuery.value(0).toString();

                itemRecord.setValue("bill_id", bill_id);
                itemRecord.setValue("product_id", productName);
                billItemModel->setRecord(i, itemRecord);
            }
            billItemModel->submitAll();
            for (int i = 0; i< transactionModel->rowCount(); ++i){
                itemRecord = transactionModel->record(i);
                itemRecord.setValue("paidOn",datetime);
                itemRecord.setValue("createdDate",datetime);
                itemRecord.setValue("bill_id",bill_id);
                itemRecord.setValue("customer_id",customer_id);
                transactionModel->setRecord(i,itemRecord);
            }
            transactionModel->submitAll();
            transactionModel->select();
            statusMsg = ui->lineEditInvoiceNo->text() + " saved successfully";
            emit signalStatusBar(statusMsg);
            clear();
        }
        setBillId();
        setTransactionTableView();
    }else{
        msgBox.setInformativeText(errors);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Ok:
               ui->lineEditCustomerName->setFocus();
               break;
           default:
               // should never be reached
               break;
         }
    }
}

void BillForm::setCodeFocus()
{
    uninstallEventFilter();
    ui->lineEditCustomerCode->setFocus();
    ui->lineEditCustomerCode->selectAll();
    ui->lineEditCustomerName->installEventFilter(this);
    ui->lineEditProductName->installEventFilter(this);
    ui->tableViewProductList->installEventFilter(this);
    ui->lineEditTax->setText("0");
    ui->lineEditDiscount->setText("0");
    emit signalCustomerNameFocused();
}

void BillForm::setProductFocus()
{
    ui->lineEditProductName->setFocus();
    ui->lineEditProductCode->selectAll();
}

void BillForm::setQuantityFocus()
{
    ui->lineEditQty->setFocus();
    ui->lineEditQty->selectAll();
}

void BillForm::clear()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",false);
        widget->setStyleSheet(styleSheet());
    }
    //uninstallEventFilter();
    setSaveButtonText(0);
//    ui->pushButtonSave->setText("Save");
    ui->pushButtonDelete->setEnabled(false);
    //ui->pushButtonSave->setEnabled(false);
    generateInvoiceNumber();
    modelFlag = 0;
    emit signalCustomerNameFocused();
    resetDataMapper();
    setTransactionTableView();
}

void BillForm::setModel(BillModel *model1, BillItemModel *model2 ,ProductsModel *model3, CustomersModel *model4)
{
    billModel = model1;
    billItemModel = model2;
    productsModel = model3;
    customersModel = model4;

    billDataMapper->setModel(billModel);
    billItemDataMapper->setModel(billItemModel);
    productDataMapper->setModel(productsModel);
    customerDataMapper->setModel(customersModel);

    billDataMapper->addMapping(ui->dateEditInvoiceDate,billModel->fieldIndex("invoiceDate"));
    billDataMapper->addMapping(ui->lineEditInvoiceNo,billModel->fieldIndex("invoiceNo"));
    billDataMapper->addMapping(ui->lineEditGrandTotal,billModel->fieldIndex("actualAmount"));
    billDataMapper->addMapping(ui->lineEditDiscount,billModel->fieldIndex("discount"));
    billDataMapper->addMapping(ui->lineEditTooBePaid,billModel->fieldIndex("totalAmount"));
    billDataMapper->addMapping(ui->lineEditCustomerName,billModel->fieldIndex("customer_id"));

    billItemDataMapper->addMapping(ui->lineEditProductName,billItemModel->fieldIndex("product_id"));
    billItemDataMapper->addMapping(ui->lineEditRate,billItemModel->fieldIndex("unitPrice"));
    billItemDataMapper->addMapping(ui->lineEditQty,billItemModel->fieldIndex("quantity"));
    billItemDataMapper->addMapping(ui->lineEditTotal,billItemModel->fieldIndex("total"));
    billItemDataMapper->addMapping(ui->lineEditUnit,billItemModel->fieldIndex("unit"));

    productDataMapper->addMapping(ui->lineEditProductCode,productsModel->fieldIndex("code"));
    productDataMapper->addMapping(ui->lineEditProductName,productsModel->fieldIndex("name"));
    productDataMapper->addMapping(ui->lineEditRate,productsModel->fieldIndex("sprice"));
    productDataMapper->addMapping(ui->lineEditUnit,productsModel->fieldIndex("unit"));

    customerDataMapper->addMapping(ui->lineEditCustomerCode,customersModel->fieldIndex("code"));
    customerDataMapper->addMapping(ui->lineEditCustomerName,customersModel->fieldIndex("name"));
    customerDataMapper->addMapping(ui->lineEditCustomerAddress,customersModel->fieldIndex("address1"));
    customerDataMapper->addMapping(ui->lineEditLimit,customersModel->fieldIndex("creditLimit"));

    ui->tableViewProductList->setModel(billItemModel);
    ui->tableViewProductList->setColumnHidden(0,true);
    ui->tableViewProductList->setColumnHidden(1,true);
    ui->tableViewProductList->setItemDelegateForColumn(4, new RightAlignDelegate);
    ui->tableViewProductList->setItemDelegateForColumn(5, new RightAlignDelegate);
    ui->tableViewProductList->setItemDelegateForColumn(6, new RightAlignDelegate);

    //ui->tableViewProductList->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewProductList));
    setCodeFocus();
    setBillId();
}

// function to validate invoice no field
bool BillForm::invoiceNoValid(){
    bool status = false;
    QString flashMsg = "";
    ui->lineEditInvoiceNo->installEventFilter(this);
    if(ui->lineEditInvoiceNo->text().length() > 0){
        if(uniqueValid(ui->lineEditInvoiceNo->text(), "invoiceNo")){
            ui->lineEditInvoiceNo->setProperty("validationError",false);
            ui->lineEditInvoiceNo->setProperty("validationSuccess",true);
            ui->lineEditInvoiceNo->setStyleSheet(styleSheet());
            validInvoiceNoFlag = 1;
            status = true;
        }else{
            flashMsg = "This Invoice No. has been already taken. Please give some other invoice no.";
            ui->lineEditInvoiceNo->setProperty("validationError",true);
            ui->lineEditInvoiceNo->setProperty("validationSuccess",false);
            ui->lineEditInvoiceNo->setStyleSheet(styleSheet());
            validInvoiceNoFlag = 0;
            status = false;
        }
    }else{
        flashMsg = "Invoice No. field is empty. Please give some values.";
        ui->lineEditInvoiceNo->setProperty("validationError",true);
        ui->lineEditInvoiceNo->setProperty("validationSuccess",false);
        ui->lineEditInvoiceNo->setStyleSheet(styleSheet());
        validInvoiceNoFlag = 0;
        status = false;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

// function to validate customer code field
bool BillForm::customerCodeValid(){
    bool status = false;
    QString flashMsg = "";
    ui->lineEditCustomerCode->installEventFilter(this);
    if(ui->lineEditCustomerCode->text().length() > 0){
        ui->lineEditCustomerCode->setProperty("validationError",false);
        ui->lineEditCustomerCode->setProperty("validationSuccess",true);
        ui->lineEditCustomerCode->setStyleSheet(styleSheet());
        validCustomerCodeFlag = 1;
        status = true;
    }else{
        flashMsg = "Customer Code field is empty. Please give some values.";
        ui->lineEditCustomerCode->setProperty("validationError",true);
        ui->lineEditCustomerCode->setProperty("validationSuccess",false);
        ui->lineEditCustomerCode->setStyleSheet(styleSheet());
        validCustomerCodeFlag = 0;
        status = false;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

//function to validate customer name field
bool BillForm::customerNameValid(){
    bool status = false;
    QString flashMsg = "";
    if(ui->lineEditCustomerName->text().length() > 0){
        status = true;
        ui->lineEditCustomerName->setProperty("validationError",false);
        ui->lineEditCustomerName->setProperty("validationSuccess",true);
        ui->lineEditCustomerName->setStyleSheet(styleSheet());
        validCustomerNameFlag = 1;
        setTransactionTableView();
    }else{
        status = false;
        flashMsg = "Customer Name field is empty. Please give some values.";
        ui->lineEditCustomerName->setProperty("validationError",true);
        ui->lineEditCustomerName->setProperty("validationSuccess",false);
        ui->lineEditCustomerName->setStyleSheet(styleSheet());
        validCustomerNameFlag = 0;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

// function to validate product code field
bool BillForm::productCodeValid(){
    bool status = false;
    QString flashMsg = "";
    FormValidation formValidation;
    ui->lineEditProductCode->installEventFilter(this);
    if(ui->lineEditProductCode->text().length() > 0){
        if(formValidation.isRecordFound("products", "code", ui->lineEditProductCode->text())){
            ui->lineEditProductCode->setProperty("validationError",false);
            ui->lineEditProductCode->setProperty("validationSuccess",true);
            ui->lineEditProductCode->setStyleSheet(styleSheet());
            validProductCodeFlag = 1;
            status = true;
        }else{
            flashMsg = "This Product not found. Please give some product code";
            ui->lineEditProductCode->setProperty("validationError",true);
            ui->lineEditProductCode->setProperty("validationSuccess",false);
            ui->lineEditProductCode->setStyleSheet(styleSheet());
            validProductCodeFlag = 0;
            status = false;
        }
    }else{
        flashMsg = "Product Code field is empty. Please give some values.";
        ui->lineEditProductCode->setProperty("validationError",true);
        ui->lineEditProductCode->setProperty("validationSuccess",false);
        ui->lineEditProductCode->setStyleSheet(styleSheet());
        validProductCodeFlag = 0;
        status = false;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

// function to validate product name field
bool BillForm::productNameValid(){
    bool status = false;
    QString flashMsg = "";
    FormValidation formValidation;
    ui->lineEditProductName->installEventFilter(this);
    if(ui->lineEditProductName->text().length() > 0){
        if(formValidation.isRecordFound("products", "name", ui->lineEditProductName->text())){
            ui->lineEditProductName->setProperty("validationError",false);
            ui->lineEditProductName->setProperty("validationSuccess",true);
            ui->lineEditProductName->setStyleSheet(styleSheet());
            validProductNameFlag = 1;
            status = true;
        }else{
            flashMsg = "This Product not found. Please give some product code";
            ui->lineEditProductName->setProperty("validationError",true);
            ui->lineEditProductName->setProperty("validationSuccess",false);
            ui->lineEditProductName->setStyleSheet(styleSheet());
            validProductNameFlag = 0;
            status = false;
        }
    }else{
        flashMsg = "Product Name field is empty. Please give some values.";
        ui->lineEditProductName->setProperty("validationError",true);
        ui->lineEditProductName->setProperty("validationSuccess",false);
        ui->lineEditProductName->setStyleSheet(styleSheet());
        validProductNameFlag = 0;
        status = false;
    }
    ui->flashMsgUp->setText(flashMsg);
    return status;
}

bool BillForm::uniqueValid(QString text, QString field)
{
    bool status = false;
    FormValidation formValidation;
    QString id;
    QSqlRecord cRecord;
    if(billDataMapper->currentIndex() < 0){
        id = "0";

    }else{
        cRecord = billModel->record(billDataMapper->currentIndex());
        id = cRecord.value("id").toString();

    }
    int count = formValidation.uniqueValid(id, text, "bill", field);
    if(count <= 0){
        status = true;
    }else{
        status = false;
    }
    return status;
}

void BillForm::setMapperIndex(QModelIndex index)
{
    if(modelFlag == 1){
        customerDataMapper->setCurrentIndex(index.row());
        setTransactionTableView();

    }else if(modelFlag == 2){
        productFormClear();
        productDataMapper->setCurrentIndex(index.row());

    }else{
        billDataMapper->setCurrentIndex(index.row());
        setBillId();
        reverseRelation();
        //ui->lineEditGiven->setText(QString::number(ui->lineEditTooBePaid->text().toInt()+ui->lineEditChange->text().toInt()));
        setTransactionTableView();
        ui->pushButtonDelete->setEnabled(true);
    }
}

void BillForm::search(QString value)
{
    QString searchValue = "code = ";
    searchValue.append(value);
    billModel->selectRow(1);
}

void BillForm::on_pushButtonClear_clicked()
{
    resetDataMapper();
    clear();
    setCodeFocus();
}

void BillForm::on_pushButtonDelete_clicked()
{
    QSqlRecord record = billModel->record(billDataMapper->currentIndex());
    QDateTime datetime = QDateTime::currentDateTime();

    record.setValue("status", "D");
    record.setValue("modifiedDate", datetime);
    billModel->setRecord(billDataMapper->currentIndex(), record);
    billModel->submitAll();
    billModel->select();
    on_pushButtonClear_clicked();

    statusMsg = ui->lineEditInvoiceNo->text() + " deleted successfully";
    emit signalStatusBar(statusMsg);
}

QDateTime BillForm::modifiedDate() const
{
    return m_modifiedDate;
}

void BillForm::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

void BillForm::onNameChanged(QString str)
{
    emit signalName(str);
}

void BillForm::setSignalFromBillForm()
{
    emit signalFromBillForm();
}

void BillForm::setFieldMaxLength()
{
//    ui->lineEditCode->setMaxLength(100);
//    ui->lineEditName->setMaxLength(200);
}

void BillForm::resetDataMapper()
{
    billDataMapper = new QDataWidgetMapper(this);
    billDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    setModel(billModel, billItemModel, productsModel, customersModel);
}

bool BillForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEditInvoiceNo){
        if(event->type() == QEvent::FocusIn)
            BillForm::invoiceNoValid();
        return false;

    }else if (obj == ui->lineEditCustomerCode){
        if(event->type() == QEvent::FocusIn)
            BillForm::customerCodeValid();
        return false;

    }else if (obj == ui->lineEditCustomerName){
        if(event->type() == QEvent::FocusIn){
            BillForm::customerNameValid();
            modelFlag = 1;
            emit signalCustomerNameFocused();
        }
        return false;

    }else if (obj == ui->lineEditProductCode){
        if(event->type() == QEvent::FocusIn)
            BillForm::productCodeValid();
        return false;

    }else if (obj == ui->lineEditProductName){
        if(event->type() == QEvent::FocusIn){
//            BillForm::productNameValid();
            modelFlag = 2;
            emit signalCustomerNameFocused();
        }
        return false;

    }else if (obj == ui->tableViewProductList){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Delete){
                QModelIndex index = ui->tableViewProductList->currentIndex();
//                int row = index.row();
//                billItemModel->deleteRowFromTable(row);
                billItemModel->removeRows(index.row(),1);
                billItemModel->submit();
                productFormClear();
                setGrandTotal();
                return false;
            }
        }
        return false;
    }
    return BillForm::eventFilter(obj, event);
}

void BillForm::uninstallEventFilter()
{
    ui->lineEditInvoiceNo->removeEventFilter(this);
    ui->lineEditCustomerCode->removeEventFilter(this);
    ui->lineEditCustomerName->removeEventFilter(this);
    ui->lineEditProductCode->removeEventFilter(this);
    ui->lineEditProductName->removeEventFilter(this);
    ui->tableViewProductList->removeEventFilter(this);
    ui->flashMsgUp->clear();
}

void BillForm::setAllValidationSuccess()
{
    validInvoiceNoFlag = validCustomerCodeFlag = validCustomerNameFlag = validProductCodeFlag = 1;
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->setProperty("validationError",false);
        widget->setProperty("validationSuccess",true);
        widget->setStyleSheet(styleSheet());
    }
}

void BillForm::generateInvoiceNumber()
{
    QDate date = QDate::currentDate();
    ui->dateEditInvoiceDate->setDate(date);
    ui->dateEditInvoiceDate->setSelectedSection(QDateEdit::NoSection);

    QSqlQueryModel model;
    QSqlQuery query;
    query.prepare("Select * from bill");
    query.exec();
    model.setQuery(query);

    QString invoiceNo;
    if(model.rowCount() == 0){
        invoiceNo = "1";
    }else{
        query.prepare("Select max(invoiceNo) from bill");
        query.exec();
        model.setQuery(query);

        int maxInvoiceNo = model.record(0).value(0).toInt() + 1;
        invoiceNo = QString::number(maxInvoiceNo);
    }
    ui->lineEditInvoiceNo->setText(invoiceNo);
}

void BillForm::setProductTotal()
{
    double qty = ui->lineEditQty->text().toDouble();
    double rate = ui->lineEditRate->text().toDouble();
    QString productTotal = QString::number(qty*rate);
    ui->lineEditTotal->setText(productTotal);
}

void BillForm::setBillId()
{
    QString bill_id;
    if (billDataMapper->currentIndex() < 0){
        bill_id = "-1";
    }else{
        QSqlRecord billrecord = billModel->record(billDataMapper->currentIndex());
        bill_id = billrecord.value("id").toString();
    }
    QString filter = "bill_id = "+bill_id;
    billItemModel->setFilter(filter);
    billItemModel->select();
}

void BillForm::addProductItem()
{
    // Initialization of local variables
    int validError = 0;
    double qty = 0.000;
    QString errors = "";

    // Initialization of message box
    QMessageBox msgBox;
    msgBox.setText("Validation Error in this forms. Please correct the form and resubmit it");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    qty = ui->lineEditQty->text().toDouble();

    // validate code field
    if(!productNameValid()){
        validError = 1;
        errors.append("\nThe Product field may be empty or not in our store");
    }

    if(qty < 0.005){
        validError = 1;
        errors.append("\n\nThe quantity field may be empty or its very low to sale");
    }
    if(validError == 0){
        if(productUpdateFlag == 1){
            bool status = billItemDataMapper->submit();
            if(status){
                billItemModel->submit();
                ui->tableViewProductList->clearSelection();
            }
        }else{
            int row = billItemModel->rowCount();
            QString bill_id;
            if (billDataMapper->currentIndex() < 0){
                bill_id = "-1";
            }else{
                QSqlRecord billrecord = billModel->record(billDataMapper->currentIndex());
                bill_id = billrecord.value("id").toString();
            }

            billItemModel->insertRows(row, 1);

            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("bill_id")),bill_id);
            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("product_id")),ui->lineEditProductName->text());
            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("unit")),ui->lineEditUnit->text());
            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("unitPrice")),ui->lineEditRate->text());
            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("quantity")),ui->lineEditQty->text());
            billItemModel->setData(billItemModel->index(row,billItemModel->fieldIndex("total")),ui->lineEditTotal->text());
            billItemModel->submit();
        }
        productFormClear();
        setGrandTotal();
        updateToBeGiven();
    }else{
        msgBox.setInformativeText(errors);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Ok:
               ui->lineEditProductName->setFocus();
               break;
           default:
               // should never be reached
               break;
        }
    }
    setRowHeight();
}

void BillForm::setGrandTotal()
{
    QSqlRecord record;
    double grandTotal = 0;
    int rowCount = billItemModel->rowCount();
    for (int i=0; i < rowCount; i++){
        record = billItemModel->record(i);
        grandTotal = grandTotal + record.value("total").toDouble();
    }
    ui->lineEditGrandTotal->setText(QString::number(grandTotal));
}

void BillForm::productUpdate(QModelIndex index)
{
    billItemDataMapper->setCurrentIndex(index.row());
    ui->tableViewProductList->setCurrentIndex(index);
    productUpdateFlag = 1;
}

void BillForm::productFormClear()
{
    ui->lineEditProductCode->clear();
    ui->lineEditProductName->clear();
    ui->lineEditQty->clear();
    ui->lineEditRate->clear();
    ui->lineEditUnit->clear();
    ui->lineEditTotal->clear();
    ui->lineEditProductName->setFocus();
    productUpdateFlag = 0;
}

void BillForm::reverseRelation()
{
    QSqlQuery customerQuery;
    customerQuery.prepare("Select * from customers where id = :customerId");
    customerQuery.bindValue(":customerId", ui->lineEditCustomerName->text());
    customerQuery.exec();
    while(customerQuery.next()){
        ui->lineEditCustomerName->setText(customerQuery.value(2).toString());
        ui->lineEditCustomerCode->setText(customerQuery.value(1).toString());
        ui->lineEditCustomerAddress->setText(customerQuery.value(6).toString());
        ui->lineEditLimit->setText(customerQuery.value(4).toString());
    }
    QString productName;
    QSqlQuery itemQuery;
    QSqlRecord itemRecord;
    for (int i = 0; i < billItemModel->rowCount(); ++i) {
        itemRecord = billItemModel->record(i);

        productName = itemRecord.value("product_id").toString();
        itemQuery.prepare("Select name from products where id = :product_name");
        itemQuery.bindValue(":product_name", productName);
        itemQuery.exec();
        itemQuery.value(0);
        while(itemQuery.next())
            productName = itemQuery.value(0).toString();

        itemRecord.setValue("product_id", productName);
        billItemModel->setRecord(i, itemRecord);
    }
    billItemModel->submit();
}

void BillForm::productFormClearForSearch()
{
    ui->lineEditProductCode->clear();
    ui->lineEditQty->clear();
    ui->lineEditRate->clear();
    ui->lineEditUnit->clear();
    ui->lineEditTotal->clear();
    ui->lineEditProductName->setFocus();
    productUpdateFlag = 0;
}

void BillForm::updateToBeGiven()
{
    double grandTotal = 0, discount = 0, tax = 0, roundOff = 0;
    int toBePaid;
    grandTotal = ui->lineEditGrandTotal->text().toDouble();
    discount =grandTotal-ui->lineEditDiscount->text().toDouble()*grandTotal/100;
    tax = discount+ui->lineEditTax->text().toDouble()*discount/100;
    toBePaid = qRound(tax);
    roundOff = toBePaid-tax;
    if(roundOff >= 0){
        ui->lineEditTooBePaid->setText(QString::number(toBePaid));
        ui->lineEditRoundOff->setText(QString::number(roundOff));
    }else{
        toBePaid = toBePaid+1;
        roundOff = 1+roundOff;
        ui->lineEditTooBePaid->setText(QString::number(toBePaid));
        ui->lineEditRoundOff->setText(QString::number(roundOff));
    }
    if(ui->lineEditGiven->text().toDouble()-ui->lineEditTooBePaid->text().toDouble() > 0)
        ui->lineEditChange->setText(QString::number(ui->lineEditGiven->text().toDouble()-ui->lineEditTooBePaid->text().toDouble()));
}

void BillForm::setTransactionTableView()
{
    if(ui->lineEditCustomerName->text().size() > 1){
        QString customerName, filter;
        QSqlQuery customerQuery,customerPaid;
        QString bill_id, billBalance;
        QSqlRecord billRecord;
        if (billDataMapper->currentIndex() < 0){
            bill_id = "-1";
            billBalance = ui->lineEditBalance->text();
        }else{
            billRecord = billModel->record(billDataMapper->currentIndex());
            bill_id = billRecord.value("id").toString();
            billBalance = billRecord.value("dueAmount").toString();
        }
        qDebug() << bill_id;
        filter = "bill_id = "+bill_id;
        transactionModel->setFilter(filter);
        transactionModel->select();
        transactionModel->setSort(0,Qt::DescendingOrder);
        ui->tableViewCustomerBalance->setModel(transactionModel);
        ui->tableViewCustomerBalance->setColumnHidden(3,false);
        ui->tableViewCustomerBalance->setColumnHidden(4,false);
        for(int i=0; i < transactionModel->columnCount(); i++){
            if(i!=3 && i!=4)
                ui->tableViewCustomerBalance->setColumnHidden(i,true);
        }
        ui->tableViewCustomerBalance->setItemDelegateForColumn(3, new RightAlignDelegate);
        ui->tableViewCustomerBalance->setItemDelegateForColumn(4,new TimeEditDelegate("dd/MM/yyyy"));
        ui->tableViewCustomerBalance->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        int balance = 0;
        customerName = ui->lineEditCustomerName->text();
        customerQuery.prepare("Select id from customers where name = :customer_name");
        customerQuery.bindValue(":customer_name", customerName);
        customerQuery.exec();
        while(customerQuery.next())
            customerName = customerQuery.value(0).toString();
        customerPaid.prepare("select * from bill where customer_id = :customerId and status = 'A' and paidStatus = 'U'");
        customerPaid.bindValue(":customerId",customerName);
        customerPaid.exec();
        while(customerPaid.next())
            balance = balance+customerPaid.value(7).toInt();

        ui->lineEditBalance->setText(billBalance);
        ui->lineEditUsed->setText(QString::number(balance));
        ui->lineEditAvailable->setText(QString::number(ui->lineEditLimit->text().toInt()-balance));
    }else{
        transactionModel->setFilter("bill_id = -1");
        transactionModel->select();
    }
    setRowHeight();
}

void BillForm::addTransaction()
{
    QDateTime datetime = QDateTime::currentDateTime();
    setTransactionTableView();
    // Initialization of local variables
    int validError = 0;
    QString errors = "";

    // Initialization of message box
    QMessageBox msgBox;
    msgBox.setText("Validation Error in this forms. Please correct the form and resubmit it");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    if(transactionModel->rowCount() > 0)
        if(ui->lineEditBalance->text().toInt() == 0)
        {
            validError =1;
            errors.append("\n This bill is already settled. There is no credit in this bill.");
        }
    // validate code field
//    if(!productNameValid()){
//        validError = 1;
//        errors.append("\nThe Product field may be empty or not in our store");
//    }

//    if(qty < 0.005){
//        validError = 1;
//        errors.append("\n\nThe quantity field may be empty or its very low to sale");
//    }
    if(validError == 0){
        int row = transactionModel->rowCount();
        QString bill_id;
        if (billDataMapper->currentIndex() < 0){
            bill_id = "-1";
        }else{
            QSqlRecord billrecord = billModel->record(billDataMapper->currentIndex());
            bill_id = billrecord.value("id").toString();
        }
        QString given = 0;
        if(ui->lineEditTooBePaid->text().toInt() < ui->lineEditGiven->text().toInt())
            given = ui->lineEditTooBePaid->text();
        else
            given = ui->lineEditGiven->text();

        transactionModel->insertRows(row, 1);

        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("bill_id")),bill_id);
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("customer_id")),ui->lineEditCustomerName->text());
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("paidAmount")),given);
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("paidOn")),datetime.toString("yyyy-MM-dd hh:mm:ss"));
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("paidBy")),"Self");
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("mode")),"Cash");
        transactionModel->setData(transactionModel->index(row,transactionModel->fieldIndex("status")),"A");
        transactionModel->submit();
        QSqlRecord transactionRecord;
        int balance = 0;
        for(int i=0; i< transactionModel->rowCount(); ++i){
            transactionRecord = transactionModel->record(i);
            balance = balance+transactionRecord.value(3).toInt();
        }
        ui->lineEditGiven->setText(given);
        calBalance();
    }else{
        msgBox.setInformativeText(errors);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Ok:
               ui->lineEditProductName->setFocus();
               break;
           default:
               // should never be reached
               break;
        }
    }
    setRowHeight();
}

void BillForm::calBalance()
{
    int paid = 0, balance =0;
    QSqlRecord transactionRecord;
    for(int i=0; i< transactionModel->rowCount(); ++i){
        transactionRecord = transactionModel->record(i);
        paid = paid+transactionRecord.value(3).toInt();
    }
    balance = ui->lineEditTooBePaid->text().toInt()-paid;
    if (balance < 0)
        balance = 0;
    ui->lineEditBalance->setText(QString::number(balance));
}

void BillForm::on_pushButtonPrint_clicked()
{
    QString fileName = QCoreApplication::applicationDirPath() + QDir::separator() + ".reports" + QDir::separator() + "bill.xml";
    report = new QtRPT(this);

//    reportModel = new QSqlRelationalTableModel;
//    reportModel->setTable("bill_item");
//    reportModel->setRelation(2, QSqlRelation("products", "id", "name"));
    //QModelIndex index = billModel->index(billDataMapper->currentIndex());
    QSqlRecord record = billModel->record(billDataMapper->currentIndex());

    reportModel = new QSqlTableModel;
    reportModel->setTable("bill_item");
    QString condition = "bill_id = " + record.value("id").toString();
    reportModel->setFilter(condition);
    reportModel->select();
    report->recordCount << reportModel->rowCount();

    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setReportValue(int&, QString&, QVariant&, int)));

    printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    //printer->setPaperSize(QPrinter::B0);
    printer->setFullPage(true);

    report->printExec(true);
}

void BillForm::setReportValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    Q_UNUSED(reportPage);
    QSqlQuery itemQuery;

    QSettings settings(QApplication::applicationDirPath() + QDir::separator() + "settings.ini", QSettings::IniFormat);
    QString companyName = settings.value("billSetting_CompanyName","").toString();
    QString companyAddress = settings.value("billSetting_City","").toString();
    QString companyPhone = settings.value("billSetting_PhoneNumber","").toString();
    QString bottomMsg = settings.value("billSetting_Message","").toString();

    if (paramName == "companyname")
        paramValue = companyName;
    if (paramName == "companyaddress")
        paramValue = companyAddress;
    if (paramName == "companyphone")
        paramValue = companyPhone;
    if (paramName == "bottommsg")
        paramValue = bottomMsg;

    QSqlRecord record = reportModel->record(recNo);
    if (paramName == "InvoiceNo")
        paramValue = ui->lineEditInvoiceNo->text();
    if (paramName == "InvoiceD")
        paramValue = ui->dateEditInvoiceDate->dateTime().toString("dd/MM/yyyy");

    if (paramName == "TotalQuantity"){
        QString billId = record.value("bill_id").toString();
        itemQuery.prepare("Select count(*) from bill_item where bill_id = :billId");
        itemQuery.bindValue(":billId", billId);
        itemQuery.exec();
        while(itemQuery.next())
            paramValue = itemQuery.value(0).toDouble();
    }

    if (paramName == "TotalAmount"){
        QString billId = record.value("bill_id").toString();
        itemQuery.prepare("Select sum(total) from bill_item where bill_id = :billId");
        itemQuery.bindValue(":billId", billId);
        itemQuery.exec();
        while(itemQuery.next())
            paramValue = QString::number(itemQuery.value(0).toDouble(), 'f', 2);
    }

    if (paramName == "ProductName") {
        if (record.value("product_id").toString().length() == 0) return;
        QString productCode = record.value("product_id").toString();
        itemQuery.prepare("Select name from products where id = :product_name");
        itemQuery.bindValue(":product_name", productCode);
        itemQuery.exec();
        while(itemQuery.next())
            paramValue = itemQuery.value(0).toString();
    }
    if (paramName == "Quantity") {
        if (record.value("quantity").toString().length() == 0) return;
        paramValue = QString::number(record.value("quantity").toDouble(), 'f', 3);
    }
    if (paramName == "Rate") {
        if (record.value("unitPrice").toString().length() == 0) return;
        paramValue = QString::number(record.value("unitPrice").toDouble(), 'f', 2);
    }
    if (paramName == "Amount") {
        if (record.value("total").toString().length() == 0) return;
        paramValue = QString::number(record.value("total").toDouble(), 'f', 2);
    }
}

void BillForm::setRowHeight()
{
    ui->tableViewCustomerBalance->resizeRowsToContents();
    ui->tableViewProductList->resizeRowsToContents();
}

void BillForm::setLanguage()
{
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

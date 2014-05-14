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

#ifndef BILLFORM_H
#define BILLFORM_H

#include "models/billitemmodel.h"
#include "models/billmodel.h"
#include "models/customersmodel.h"
#include "models/productsmodel.h"
#include "models/formvalidation.h"
#include "models/transactionmodel.h"
#include "rightaligndelegate.h"

#include "qtrpt.h"

#include <QWidget>
#include <QValidator>
#include <QIntValidator>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QEvent>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QModelIndex>
#include <QKeyEvent>
#include <QSqlRelationalDelegate>
#include <QPrinter>

namespace Ui {
class BillForm;
}

class BillForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)
    QString statusMsg;

public:
    explicit BillForm(QWidget *parent = 0);
    ~BillForm();
    void setCodeFocus();
    void setProductFocus();
    void setQuantityFocus();
    void setModel(BillModel *model1, BillItemModel *model2, ProductsModel *model3, CustomersModel *model4);
    void setMapperIndex(QModelIndex index);
    void search(QString value);
    QDateTime modifiedDate() const;
    void setModifiedDate(QDateTime modifiedDate);
    void clear();
    int validInvoiceNoFlag, validCustomerCodeFlag, validCustomerNameFlag;
    int validProductCodeFlag, validProductNameFlag;
    void setFieldMaxLength();
    int modelFlag;
    int productUpdateFlag;
    void productFormClearForSearch();
    void settranslate();

signals:
    void signalName(QString str);
    void signalFromBillForm();
    void signalStatusBar(QString str);
    void signalCustomerNameFocused();

private:
    Ui::BillForm *ui;
    BillItemModel *billItemModel;
    BillModel *billModel;
    ProductsModel *productsModel;
    CustomersModel *customersModel;
    QSqlTableModel *transactionModel;

    QDataWidgetMapper *billDataMapper;
    QDataWidgetMapper *billItemDataMapper;
    QDataWidgetMapper *productDataMapper;
    QDataWidgetMapper *customerDataMapper;

    QDateTime m_modifiedDate;
    FormValidation *formValidation;

    QtRPT *report;
    QPrinter *printer;
    QSqlTableModel *reportModel;

private slots:
    void save();
    bool invoiceNoValid();
    bool customerCodeValid();
    bool customerNameValid();
    bool productCodeValid();
    bool productNameValid();
    void on_pushButtonClear_clicked();
    void on_pushButtonDelete_clicked();
    void onNameChanged(QString str);
    bool uniqueValid(QString text, QString field);
    void setSignalFromBillForm();
    bool eventFilter(QObject *obj, QEvent *event);
    void resetDataMapper();
    void setAllValidationSuccess();
    void uninstallEventFilter();
    void generateInvoiceNumber();
    void setProductTotal();
    void setBillId();
    void addProductItem();
    void setGrandTotal();
    void productUpdate(QModelIndex index);
    void productFormClear();
    void reverseRelation();
    void updateToBeGiven();
    void addTransaction();
    void setTransactionTableView();
    void setReportValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void on_pushButtonPrint_clicked();
    void calBalance();
    void setRowHeight();
};

#endif // BILLFORM_H

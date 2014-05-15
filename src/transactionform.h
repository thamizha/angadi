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

#ifndef TRANSACTIONFORM_H
#define TRANSACTIONFORM_H

#include "models/formvalidation.h"
#include "models/transactionmodel.h"
#include "models/billmodel.h"

#include <QWidget>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QEvent>
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlQuery>


namespace Ui {
class TransactionForm;
}

class TransactionForm : public QWidget
{
    Q_OBJECT
    QString statusMsg;

public:
    explicit TransactionForm(QWidget *parent = 0);
    ~TransactionForm();
    void setModel(TransactionModel *model);
    void clear();
    void setFieldMaxLength();
    void setMapperIndex(QModelIndex index);
    void setCodeFocus();
    void setNameFocus();
    void settranslate();
    void setSaveButtonText(qint8);

signals:
    void signalName(QString);
    void signalFromTransactionForm();
    void signalStatusBar(QString);
    void signalUpdated();

private:
    Ui::TransactionForm *ui;
    TransactionModel *transactionModel;
    QDataWidgetMapper *dataMapper;
    QDateTime m_modifiedDate;
    FormValidation *formValidation;
    BillModel *billModel;

private slots:
    void generateDate();
    void save();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void search(QString value);
    void onNameChanged(QString str);
    void setSignalFromTransactionForm();
    void resetDataMapper();
    bool eventFilter(QObject *obj, QEvent *event);
    void uninstallEventFilter();
    void setAllValidationSuccess();
    bool invoiceNoValid();
    bool amountValid();
    bool billStatus();
};

#endif // TRANSACTIONFORM_H

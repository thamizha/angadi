/*****************************************************************************
 * productsmodel.h
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

#include "transactionmodel.h"
#include "../connection.h"
#include "transactionform.h"

#include <QDebug>
#include <QTranslator>
#include <QSettings>
#include <QApplication>

TransactionModel::TransactionModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{

    //    Language setup
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString content = settings.value("s_language","").toString();
    QString lanInvoiceNumber;
    QString lanCustomerName;
    QString lanPaidAmount;
    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanInvoiceNumber = TransactionForm::tr("Invoice Number");
        lanCustomerName = TransactionForm::tr("Customer Name");
        lanPaidAmount = TransactionForm::tr("Paid Amount");
     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanInvoiceNumber = TransactionForm::tr("Invoice Number");
        lanCustomerName = TransactionForm::tr("Customer Name");
        lanPaidAmount = TransactionForm::tr("Paid Amount");
    }

    setTable("transactions");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(fieldIndex("bill_id"), Qt::Horizontal, lanInvoiceNumber);
    setHeaderData(fieldIndex("customer_id"), Qt::Horizontal, lanCustomerName);
    setHeaderData(fieldIndex("paidAmount"), Qt::Horizontal, lanPaidAmount);
    setRelation(fieldIndex("bill_id"), QSqlRelation("bill", "id", "invoiceNo"));
    setRelation(fieldIndex("customer_id"), QSqlRelation("customers", "id", "name"));
//    relationModel(1)->setFilter("paidStatus = 'U' and status = 'A'");
//    setHeaderData(fieldIndex("products_id"), Qt::Horizontal, QObject::tr("Product Name"));
//    setFilter("bill.status = 'A'");
//    relationModel(3)->setFilter("status = 'A'");
//    setSort(fieldIndex("id"),Qt::AscendingOrder);
    select();
//    qDebug() << rowCount();
}

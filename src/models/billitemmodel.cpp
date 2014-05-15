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

#include "billitemmodel.h"
#include "../connection.h"
#include "billform.h"
#include <QTranslator>
#include <QSettings>
#include <QApplication>
BillItemModel::BillItemModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    //    Language setup
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString content = settings.value("s_language","").toString();
    QString lanProductName;
    QString lanUnit;
    QString lanUnitPrice;
    QString lanQuantity;
    QString lanTotal;
    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanProductName = BillForm::tr("Product Name");
        lanUnit = BillForm::tr("Unit");
        lanUnitPrice = BillForm::tr("Unit Price");
        lanQuantity = BillForm::tr("Quantity");
        lanTotal = BillForm::tr("Total");
     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanProductName = BillForm::tr("Product Name");
        lanUnit = BillForm::tr("Unit");
        lanUnitPrice = BillForm::tr("Unit Price");
        lanQuantity = BillForm::tr("Quantity");
        lanTotal = BillForm::tr("Total");
    }


    setTable("bill_item");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(fieldIndex("product_id"), Qt::Horizontal, lanProductName);
    setHeaderData(fieldIndex("unit"), Qt::Horizontal, lanUnit);
    setHeaderData(fieldIndex("unitPrice"), Qt::Horizontal, lanUnitPrice);
    setHeaderData(fieldIndex("quantity"), Qt::Horizontal, lanQuantity);
    setHeaderData(fieldIndex("total"), Qt::Horizontal, lanTotal);
//    setRelation(fieldIndex("product_id"), QSqlRelation("products", "id", "name"));
//    setHeaderData(fieldIndex("products_id"), Qt::Horizontal, QObject::tr("Product Name"));
//    setFilter("bill.status = 'A'");
//    relationModel(3)->setFilter("status = 'A'");
//    setSort(fieldIndex("id"),Qt::AscendingOrder);
    select();
}

/*****************************************************************************
 * customersmodel.cpp
 *
 * Created: 26/04/2014 by selvam
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

#include "customersmodel.h"
#include "customerform.h"
#include <QTranslator>
#include <QSettings>
#include <QApplication>

CustomersModel::CustomersModel(QObject *parent) :
    QSqlTableModel(parent)
{

    //    Language setup
    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString content = settings.value("s_language","").toString();
    QString lanCode;
    QString lanName;
    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanCode = CustomerForm::tr("Code");
        lanName = CustomerForm::tr("Name");
     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        lanCode = CustomerForm::tr("Code");
        lanName = CustomerForm::tr("Name");
    }

    setTable("customers");
    setHeaderData(fieldIndex("code"), Qt::Horizontal, lanCode);
    setHeaderData(fieldIndex("name"), Qt::Horizontal, lanName);
    setFilter("status = 'A'");
    setSort(fieldIndex("id"),Qt::AscendingOrder);
    select();
}

CustomersModel::~CustomersModel()
{

}

/*****************************************************************************
 * billsettings.cpp
 *
 * Created: 14/05/2014 by vijay
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
 * Vijay @ Dhanasekaran <vijay.kuruntham.gmail.com>
 *****************************************************************************/

#include "billsettings.h"
#include "ui_billsettings.h"

#include <QDebug>
#include <QString>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QTranslator>

BillSettings::BillSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BillSettings)
{
    ui->setupUi(this);

    setLanguage();
}

BillSettings::~BillSettings()
{
    delete ui;
}

void BillSettings::settranslate()
{
    ui->retranslateUi(this);
}

void BillSettings::on_pushButtonSave_clicked()
{
    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    settings.setValue("billSetting_CompanyName",ui->lineEditCompanyName->text());
    settings.setValue("billSetting_City",ui->lineEditCity->text());
    settings.setValue("billSetting_PhoneNumber",ui->lineEditPhoneNumber->text());
    settings.setValue("billSetting_Message",ui->lineEditMessage->text());
    QMessageBox Msgbox;
    Msgbox.setText("Saved Suceessfully");
    Msgbox.exec();
}

void BillSettings::on_pushButtonClose_clicked()
{
    this->hide();
}

void BillSettings::setLanguage()
{
    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);

    ui->lineEditCity->setText(settings.value("billSetting_City","").toString());
    ui->lineEditCompanyName->setText(settings.value("billSetting_CompanyName","").toString());
    ui->lineEditMessage->setText(settings.value("billSetting_Message","").toString());
    ui->lineEditPhoneNumber->setText(settings.value("billSetting_PhoneNumber","").toString());

    //Language setup
//    QString app_path;
//    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
//    QSettings settings(app_path,QSettings::NativeFormat);
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

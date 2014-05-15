/*****************************************************************************
 * settings.cpp
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

#include "settings.h"
#include "ui_settings.h"

#include <QDebug>
#include <QString>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QTranslator>
#include <QDialog>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->comboBoxLanguage->addItem("தமிழ்");
    ui->comboBoxLanguage->addItem("English");

    setLanguage();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::settingsModal()
{
    qDebug() << "Triggered";
    QDialog preferenceDialog(this);
    preferenceDialog.setModal(true);

    preferenceDialog.exec();
//    preferenceDialog.show();
}

void Settings::settranslate()
{
    ui->retranslateUi(this);
}


void Settings::on_pushButtonSave_clicked()
{
    qDebug() << ui->comboBoxLanguage->currentText();

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Preference settings", "Need to <b>restart</b> the application ? ",QMessageBox::Ok|QMessageBox::Cancel);
      if (reply == QMessageBox::Ok) \
      {
        QString s_language;
        if(ui->comboBoxLanguage->currentText() == "தமிழ்")
        s_language = "tamil_language";
        if(ui->comboBoxLanguage->currentText() == "English")
        s_language = "english_language";

        qDebug() << s_language;

        QString app_path;
        app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
        QSettings settings(app_path,QSettings::NativeFormat);
        settings.setValue("s_language",s_language);
        settings.setValue("s_companyName",ui->lineEditComapanyName->text());
        settings.setValue("s_address",ui->lineEditAddress->text());
        settings.setValue("s_tinNumber",ui->lineEditTinNumber->text());
        settings.setValue("s_phoneNumber",ui->lineEditPhoneNumber->text());


        QMessageBox Msgbox;
        Msgbox.setText("Preferences are saved Suceessfully");
        Msgbox.exec();

        QProcess::startDetached(QApplication::applicationFilePath());       //Restart the application
        exit(2);

      }
      else
      {
          QString app_path;
          app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
          QSettings settings(app_path,QSettings::NativeFormat);

          if(settings.value("s_language","").toString() == "tamil_languag")
              ui->comboBoxLanguage->setCurrentIndex(0);
          if(settings.value("s_language","").toString() == "english_language")
              ui->comboBoxLanguage->setCurrentIndex(1);

          ui->lineEditAddress->setText(settings.value("s_address","").toString());
          ui->lineEditComapanyName->setText(settings.value("s_companyName","").toString());
          ui->lineEditPhoneNumber->setText(settings.value("s_phoneNumber","").toString());
          ui->lineEditTinNumber->setText(settings.value("s_tinNumber","").toString());
      }
}

void Settings::on_pushButtonClose_clicked()
{
    this->hide();
}

void Settings::setLanguage()
{
    QString app_path;
    app_path = QApplication::applicationDirPath()+"/settingsfile.ini";
    QSettings settings(app_path,QSettings::NativeFormat);

    if(settings.value("s_language","").toString() == "tamil_languag")
        ui->comboBoxLanguage->setCurrentIndex(0);
    if(settings.value("s_language","").toString() == "english_language")
        ui->comboBoxLanguage->setCurrentIndex(1);

    ui->lineEditAddress->setText(settings.value("s_address","").toString());
    ui->lineEditComapanyName->setText(settings.value("s_companyName","").toString());
    ui->lineEditPhoneNumber->setText(settings.value("s_phoneNumber","").toString());
    ui->lineEditTinNumber->setText(settings.value("s_tinNumber","").toString());

    //    Language setup
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

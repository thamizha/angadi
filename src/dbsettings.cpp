/*****************************************************************************
 * dbsettings.cpp
 *
 * Created: 16/05/2014 by vijay
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

#include "dbsettings.h"
#include "ui_dbsettings.h"

#include <QSettings>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
DBSettings::DBSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBSettings)
{
    ui->setupUi(this);

    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::IniFormat);

    ui->lineEditHostName->setText(settings.value("s_hostName","").toString());
    ui->lineEditPort->setText(settings.value("s_port","").toString());
    ui->lineEditUsername->setText(settings.value("s_userName","").toString());
    ui->lineEditPassword->setText(settings.value("s_password","").toString());
}

DBSettings::~DBSettings()
{
    delete ui;
}

void DBSettings::on_pushButtonSave_clicked()
{
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::IniFormat);

    settings.setValue("s_hostName",ui->lineEditHostName->text());
    settings.setValue("s_port",ui->lineEditPort->text());
    settings.setValue("s_userName",ui->lineEditUsername->text());
    settings.setValue("s_password",ui->lineEditPassword->text());

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Database settings", "Database settings are saved Suceessfully",QMessageBox::Ok|QMessageBox::Cancel);

    //qDebug() << "exit call";
    QProcess::startDetached(QApplication::applicationFilePath());       //Restart the application
    exit(1);
}

void DBSettings::on_pushButtonClose_clicked()
{
    exit(0);
}

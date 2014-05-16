/*****************************************************************************
 * connection.cpp
 *
 * Created: 18/04/2014 by selvam
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
 *
 *****************************************************************************/

#include "connection.h"
#include "settings.h"
#include <QMessageBox>

Connection::Connection(QObject *parent) :
    QObject(parent)
{
    DBSettings *dbsettings = new DBSettings();

    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::NativeFormat);

    QString hostName = settings.value("s_hostName","").toString();
    qint8 port = settings.value("s_port","").toInt();
    QString username = settings.value("s_userName","").toString();
    QString password = settings.value("s_password","").toString();

    if(hostName.length() <= 0 && username.length() <= 0)
        dbsettings->exec();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setPort(port);
    db.setDatabaseName("angadi");
    db.setUserName(username);
    db.setPassword(password);
    //    db.exec("CREATE SCHEMA `angadi` DEFAULT CHARACTER SET utf8 ;");

    bool status = db.open();
    if(status){
        createSqliteTables();
    }else{
        QMessageBox msgBox;
        msgBox.setText("<B><u>Note:</u></B>");
        msgBox.setInformativeText("Database not exists in your mysql server. Create a database in the name of <B>angadi</b> in your mysql server, Until then you cannot use our application.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
           case QMessageBox::Ok:
               dbsettings->exec();
               break;
           default:
               // should never be reached
               break;
         }
    }

    if(!db.open())
        exit(1);
}

Connection::~Connection()
{
}

void Connection::createSqliteTables()
{
//    bill table creation
//    db.exec("CREATE SCHEMA `angadi` DEFAULT CHARACTER SET utf8 ;");
//    db.exec("Use angadi");
    db.exec("CREATE TABLE IF NOT EXISTS `bill` ("
              "`id` int(11) NOT NULL AUTO_INCREMENT,"
              "`invoiceNo` int(11) NOT NULL,"
              "`invoiceDate` datetime NOT NULL,"
              "`customer_id` int(11) DEFAULT NULL,"
              "`actualAmount` double NOT NULL DEFAULT '0',"
              "`discount` double NOT NULL DEFAULT '0',"
              "`totalAmount` double NOT NULL DEFAULT '0',"
              "`dueAmount` double NOT NULL DEFAULT '0',"
              "`paidStatus` enum('P','U') NOT NULL COMMENT 'P => Paid; U => Unpaid',"
              "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
              "`createdDate` datetime DEFAULT NULL,"
              "`modifiedDate` datetime DEFAULT NULL,"
              "`modifiedBy` datetime DEFAULT NULL,"
             "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `bill_item` ("
          "`id` int(11) NOT NULL AUTO_INCREMENT,"
          "`bill_id` int(11) NOT NULL,"
          "`product_id` int(11) NOT NULL,"
          "`unit` varchar(45) NOT NULL,"
          "`unitPrice` double NOT NULL DEFAULT '0',"
          "`quantity` double NOT NULL DEFAULT '0',"
          "`total` double NOT NULL DEFAULT '0',"
         "PRIMARY KEY (`id`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `categories` ("
          "`id` int(11) NOT NULL AUTO_INCREMENT,"
          "`code` varchar(100) NOT NULL,"
          "`name` varchar(200) NOT NULL,"
          "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Delete',"
          "`createdDate` datetime DEFAULT NULL,"
          "`modifiedDate` datetime DEFAULT NULL,"
          "PRIMARY KEY (`id`)"
        ") ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `customers` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`code` varchar(100) NOT NULL,"
            "`name` varchar(200) NOT NULL,"
            "`type` varchar(45) NOT NULL,"
            "`creditLimit` double NOT NULL,"
            "`gender` varchar(45) DEFAULT NULL,"
            "`contactPerson` varchar(200) DEFAULT NULL,"
            "`address1` varchar(255) DEFAULT NULL,"
            "`address2` varchar(255) DEFAULT NULL,"
            "`city` varchar(100) DEFAULT NULL,"
            "`state` varchar(100) DEFAULT NULL,"
            "`country` varchar(100) DEFAULT NULL,"
            "`pincode` varchar(10) DEFAULT NULL,"
            "`phone1` varchar(20) DEFAULT NULL,"
            "`phone2` varchar(20) DEFAULT NULL,"
            "`mobile1` varchar(20) DEFAULT NULL,"
            "`mobile2` varchar(20) DEFAULT NULL,"
            "`email` varchar(80) DEFAULT NULL,"
            "`website` varchar(80) DEFAULT NULL,"
            "`notes` text,"
            "`status` enum('A','I','D') NOT NULL DEFAULT 'A',"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` varchar(45) DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT NULL,"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `products` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`code` varchar(100) NOT NULL,"
            "`name` varchar(200) NOT NULL,"
            "`unit` varchar(100) NOT NULL,"
            "`category_id` int(11) NOT NULL,"
            "`mrp` double NOT NULL,"
            "`sprice` double NOT NULL,"
            "`wholeSalePrice` double NOT NULL,"
            "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` datetime DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT NULL,"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `transactions` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`bill_id` int(11) NOT NULL,"
            "`customer_id` int(11) NOT NULL,"
            "`paidAmount` double NOT NULL DEFAULT '0',"
            "`paidOn` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',"
            "`paidBy` varchar(150) DEFAULT NULL,"
            "`mode` varchar(45) NOT NULL,"
            "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` datetime DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT NULL,"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    db.exec("CREATE TABLE IF NOT EXISTS `users` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`username` varchar(100) NOT NULL,"
            "`password` varchar(60) NOT NULL,"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` datetime DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT '0',"
            "`status` enum('A','I','D','N') NOT NULL DEFAULT 'N',"
            "`rememberMe` enum('Y','N') DEFAULT 'N',"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;);");

}


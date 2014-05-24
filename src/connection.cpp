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
    // Mysql
    /*dbsettings = new DBSettings();

    bool isDbParamsCorrect = checkConnectionParams();

    bool isMysqlUsernameCorrect = false;
    if(isDbParamsCorrect){
        isMysqlUsernameCorrect = checkMysqlUsername();
    }

    bool iStatus = false;
    if(isDbParamsCorrect && isMysqlUsernameCorrect){
        iStatus = openConnection("angadi");
    }else{
        QMessageBox msgBox;
        msgBox.setText("<B><u>Note:</u></B>");
        //msgBox.setInformativeText("Database not exists in your mysql server. Create a database in the name of <B>angadi</b> in your mysql server, Until then you cannot use our application.");
        msgBox.setInformativeText("Given mysql server credentials may be incorrect. Please ensure that hostname, username, and password are valid, Until then you cannot use our application.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        dbsettings->exec();
    }

    if(!iStatus){
        createAndOpenDb();
    }

    if(!db.open())
        exit(1);*/

    // Sqlite
    if(!QFile::exists(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite")){
        createSqliteTables();
    }else{
         db = QSqlDatabase::addDatabase("QSQLITE");
         db.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite");
         db.open();
    }
}

Connection::~Connection()
{
}

void Connection::createSqliteTables()
{
    // Sqlite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite");
    db.open();

    // // bill table creation
     db.exec("CREATE TABLE IF NOT EXISTS `bill` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`invoiceNo` int(11) NOT NULL, "
     "`invoiceDate` datetime NOT NULL, "
     "`customer_id` int(11) DEFAULT NULL, "
     "`actualAmount` double NOT NULL DEFAULT '0', "
     "`discount` double NOT NULL DEFAULT '0', "
     "`totalAmount` double NOT NULL DEFAULT '0', "
     "`dueAmount` double NOT NULL DEFAULT '0', "
     "`paidStatus` CHAR(1) NOT NULL, "
     "`status` CHAR(1) NOT NULL DEFAULT 'A', "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` datetime DEFAULT NULL, "
     "`modifiedBy` datetime DEFAULT NULL "
     ")");

    // // bill_item table creation
     db.exec("CREATE TABLE IF NOT EXISTS `bill_item` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`bill_id` int(11) NOT NULL, "
     "`product_id` int(11) NOT NULL, "
     "`unit` varchar(45) NOT NULL, "
     "`unitPrice` double NOT NULL DEFAULT '0', "
     "`quantity` double NOT NULL DEFAULT '0', "
     "`total` double NOT NULL DEFAULT '0' "
     ")");

    // // categories table creation
     db.exec("CREATE TABLE IF NOT EXISTS `categories` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`code` varchar(100) NOT NULL, "
     "`name` varchar(200) NOT NULL, "
     "`status` CHAR(1) NOT NULL DEFAULT 'A', "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` datetime DEFAULT NULL "
     ")");

    // default category
    db.exec("INSERT INTO `categories` (`code`, `name`, `status`) VALUES ('1001', 'GENERAL', 'A');");

    // // customers table creation
     db.exec("CREATE TABLE IF NOT EXISTS `customers` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`code` varchar(100) NOT NULL, "
     "`name` varchar(200) NOT NULL, "
     "`type` varchar(45) NOT NULL, "
     "`creditLimit` double NOT NULL, "
     "`gender` varchar(45) DEFAULT NULL, "
     "`contactPerson` varchar(200) DEFAULT NULL, "
     "`address1` varchar(255) DEFAULT NULL, "
     "`address2` varchar(255) DEFAULT NULL, "
     "`city` varchar(100) DEFAULT NULL, "
     "`state` varchar(100) DEFAULT NULL, "
     "`country` varchar(100) DEFAULT NULL, "
     "`pincode` varchar(10) DEFAULT NULL, "
     "`phone1` varchar(20) DEFAULT NULL, "
     "`phone2` varchar(20) DEFAULT NULL, "
     "`mobile1` varchar(20) DEFAULT NULL, "
     "`mobile2` varchar(20) DEFAULT NULL, "
     "`email` varchar(80) DEFAULT NULL, "
     "`website` varchar(80) DEFAULT NULL, "
     "`notes` text, "
     "`status` CHAR(1) NOT NULL DEFAULT 'A', "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` varchar(45) DEFAULT NULL, "
     "`modifiedBy` int(11) DEFAULT NULL "
     ")");

    // default customer
    db.exec("INSERT INTO `customers` (`code`, `name`, `type`, `creditLimit`, `gender`, `status`) VALUES ('1001', 'GENERAL', 'Retailer', '0', 'Male', 'A');");

    // // products table creation
     db.exec("CREATE TABLE IF NOT EXISTS `products` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`code` varchar(100) NOT NULL, "
     "`name` varchar(200) NOT NULL, "
     "`unit` varchar(100) NOT NULL, "
     "`category_id` int(11) NOT NULL, "
     "`mrp` double NOT NULL, "
     "`sprice` double NOT NULL, "
     "`wholeSalePrice` double NOT NULL, "
     "`status` CHAR(1) NOT NULL DEFAULT 'A', "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` datetime DEFAULT NULL, "
     "`modifiedBy` int(11) DEFAULT NULL "
     ")");

    // // transactions table creation
     db.exec("CREATE TABLE IF NOT EXISTS `transactions` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`bill_id` int(11) NOT NULL, "
     "`customer_id` int(11) NOT NULL, "
     "`paidAmount` double NOT NULL DEFAULT '0', "
     "`paidOn` datetime NOT NULL DEFAULT '0000-00-00 00:00:00', "
     "`paidBy` varchar(150) DEFAULT NULL, "
     "`mode` varchar(45) NOT NULL, "
     "`status` CHAR(1) NOT NULL DEFAULT 'A', "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` datetime DEFAULT NULL, "
     "`modifiedBy` int(11) DEFAULT NULL "
     ")");

    // // user table creation
     db.exec("CREATE TABLE IF NOT EXISTS `users` ( "
     "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
     "`username` varchar(100) NOT NULL, "
     "`password` varchar(60) NOT NULL, "
     "`createdDate` datetime DEFAULT NULL, "
     "`modifiedDate` datetime DEFAULT NULL, "
     "`modifiedBy` int(11) DEFAULT '0', "
     "`status` CHAR(1) NOT NULL DEFAULT 'N', "
     "`rememberMe` CHAR(1) DEFAULT 'N' "
     ")");

    // default user creation
     db.exec("INSERT INTO `users` (`username`, `password`, `createdDate`, `modifiedDate`, `modifiedBy`, `status`) "
     "VALUES ('admin', 'admin', '', '', '', 'A');");

    // Mysql
//    bill table creation
/*    db.exec("CREATE TABLE IF NOT EXISTS `bill` ("
              "`id` int(11) NOT NULL AUTO_INCREMENT,"
              "`invoiceNo` int(11) NOT NULL,"
              "`invoiceDate` datetime NOT NULL,"
              "`customer_id` int(11) DEFAULT NULL,"
              "`actualAmount` double(11,2) NOT NULL DEFAULT '0.00',"
              "`discount` double(11,2) NOT NULL DEFAULT '0.00',"
              "`totalAmount` double(11,2) NOT NULL DEFAULT '0.00',"
              "`dueAmount` double(11,2) NOT NULL DEFAULT '0.00',"
              "`paidStatus` enum('P','U') NOT NULL COMMENT 'P => Paid; U => Unpaid',"
              "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
              "`createdDate` datetime DEFAULT NULL,"
              "`modifiedDate` datetime DEFAULT NULL,"
              "`modifiedBy` datetime DEFAULT NULL,"
             "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//    bill_item table creation
    db.exec("CREATE TABLE IF NOT EXISTS `bill_item` ("
          "`id` int(11) NOT NULL AUTO_INCREMENT,"
          "`bill_id` int(11) NOT NULL,"
          "`product_id` int(11) NOT NULL,"
          "`unit` varchar(45) NOT NULL,"
          "`unitPrice` double(11,2) NOT NULL DEFAULT '0.00',"
          "`quantity` double(11,2) NOT NULL DEFAULT '0.00',"
          "`total` double(11,2) NOT NULL DEFAULT '0.00',"
         "PRIMARY KEY (`id`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//    categories table creation
    db.exec("CREATE TABLE IF NOT EXISTS `categories` ("
          "`id` int(11) NOT NULL AUTO_INCREMENT,"
          "`code` varchar(100) NOT NULL,"
          "`name` varchar(200) NOT NULL,"
          "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Delete',"
          "`createdDate` datetime DEFAULT NULL,"
          "`modifiedDate` datetime DEFAULT NULL,"
          "PRIMARY KEY (`id`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//        default category
        db.exec("INSERT INTO `categories` (`code`, `name`, `status`) VALUES ('1001', 'GENERAL', 'A');");

//    customers table creation
    db.exec("CREATE TABLE IF NOT EXISTS `customers` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`code` varchar(100) NOT NULL,"
            "`name` varchar(200) NOT NULL,"
            "`type` varchar(45) NOT NULL,"
            "`creditLimit` double(11,2) NOT NULL DEFAULT '0.00',"
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
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//    default customer
    db.exec("INSERT INTO `customers` (`code`, `name`, `type`, `creditLimit`, `gender`, `status`) VALUES ('1001', 'GENERAL', 'Retailer', '0', 'Male', 'A');");

//    products table creation
    db.exec("CREATE TABLE IF NOT EXISTS `products` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`code` varchar(100) NOT NULL,"
            "`name` varchar(200) NOT NULL,"
            "`unit` varchar(100) NOT NULL,"
            "`category_id` int(11) NOT NULL,"
            "`mrp` double(11,2) NOT NULL DEFAULT '0.00',"
            "`sprice` double(11,2) NOT NULL DEFAULT '0.00',"
            "`wholeSalePrice` double(11,2) NOT NULL DEFAULT '0.00',"
            "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` datetime DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT NULL,"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//    transactions table creation
    db.exec("CREATE TABLE IF NOT EXISTS `transactions` ("
            "`id` int(11) NOT NULL AUTO_INCREMENT,"
            "`bill_id` int(11) NOT NULL,"
            "`customer_id` int(11) NOT NULL,"
            "`paidAmount` double(11,2) NOT NULL DEFAULT '0.00',"
            "`paidOn` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',"
            "`paidBy` varchar(150) DEFAULT NULL,"
            "`mode` varchar(45) NOT NULL,"
            "`status` enum('A','I','D') NOT NULL DEFAULT 'A' COMMENT 'A => Active; I => Inactive; D => Deleted',"
            "`createdDate` datetime DEFAULT NULL,"
            "`modifiedDate` datetime DEFAULT NULL,"
            "`modifiedBy` int(11) DEFAULT NULL,"
            "PRIMARY KEY (`id`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

//    users table creation
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
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8;);");*/
}

/*bool Connection::checkConnectionParams()
{
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::IniFormat);

    hostName = settings.value("s_hostName","").toString();
    port = settings.value("s_port","").toInt();
    username = settings.value("s_userName","").toString();
    password = settings.value("s_password","").toString();

    if(hostName.length() <= 0 || username.length() <= 0)
        dbsettings->exec();

    bool status = false;
    if(openConnection(""))
        status = true;
    else
        dbsettings->exec();

    return status;
}

void Connection::createAndOpenDb()
{
    bool status = openConnection("");

    QSqlQuery query;
    if(status){
        query.exec("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = 'angadi';");

        if(!query.next())
            db.exec("CREATE SCHEMA `angadi` DEFAULT CHARACTER SET utf8 ;");

        if(openConnection("angadi"))
            createSqliteTables();
    }
}

void Connection::closeDb()
{
    QString connection;
    if(db.open()){
        connection = db.connectionName();
        db.close();
        db = QSqlDatabase();
        db.removeDatabase(connection);
    }
}

bool Connection::openConnection(QString dbName)
{
    closeDb();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);

    if(port > 0)
        db.setPort(port);

    if(dbName.length() > 0)
        db.setDatabaseName(dbName);

    db.setUserName(username);
    db.setPassword(password);
    return db.open(username, password);
}

bool Connection::checkMysqlUsername()
{
    bool status = openConnection("");

    bool lStatus = false;
    QSqlQuery query;
    if(status){
        query.prepare("SELECT EXISTS(SELECT 1 FROM mysql.user WHERE user = :username)");
        query.bindValue(":username", username);
        query.exec();
        if(query.next())
            lStatus = true;
    }
    return lStatus;
}*/

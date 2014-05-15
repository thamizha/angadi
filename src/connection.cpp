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

Connection::Connection(QObject *parent) :
    QObject(parent)
{
//    Mysql
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("angadi");
    db.setUserName("root");
    db.setPassword("");
    db.open();

////    Sqlite
//    if(!QFile::exists(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite")){
//        createSqliteTables();
//    }else{
//        db =  QSqlDatabase::addDatabase("QSQLITE");
//        db.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite");
//        db.open();
//    }
}

Connection::~Connection()
{
}

void Connection::createSqliteTables()
{
//    db =  QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "angadi.sqlite");
//    db.open();

//    //    bill table creation
//            db.exec("CREATE TABLE IF NOT EXISTS `bill` ( "
//                    "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                    "`invoiceNo` int(11) NOT NULL, "
//                    "`invoiceDate` datetime NOT NULL, "
//                    "`customer_id` int(11) DEFAULT NULL, "
//                    "`actualAmount` double NOT NULL DEFAULT '0', "
//                    "`discount` double NOT NULL DEFAULT '0', "
//                    "`totalAmount` double NOT NULL DEFAULT '0', "
//                    "`dueAmount` double NOT NULL DEFAULT '0', "
//                    "`paidStatus` CHAR(1) NOT NULL, "
//                    "`status` CHAR(1) NOT NULL DEFAULT 'A', "
//                    "`createdDate` datetime DEFAULT NULL, "
//                    "`modifiedDate` datetime DEFAULT NULL, "
//                    "`modifiedBy` datetime DEFAULT NULL "
//                  ")");

//    //            bill_item table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `bill_item` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`bill_id` int(11) NOT NULL, "
//                            "`product_id` int(11) NOT NULL, "
//                            "`unit` varchar(45) NOT NULL, "
//                            "`unitPrice` double NOT NULL DEFAULT '0', "
//                            "`quantity` double NOT NULL DEFAULT '0', "
//                            "`total` double NOT NULL DEFAULT '0' "
//                          ")");

//    //                categories table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `categories` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`code` varchar(100) NOT NULL, "
//                            "`name` varchar(200) NOT NULL, "
//                            "`status` CHAR(1) NOT NULL DEFAULT 'A', "
//                            "`createdDate` datetime DEFAULT NULL, "
//                            "`modifiedDate` datetime DEFAULT NULL "
//                          ")");

//    //                customers table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `customers` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`code` varchar(100) NOT NULL, "
//                            "`name` varchar(200) NOT NULL, "
//                            "`type` varchar(45) NOT NULL, "
//                            "`creditLimit` double NOT NULL, "
//                            "`gender` varchar(45) DEFAULT NULL, "
//                            "`contactPerson` varchar(200) DEFAULT NULL, "
//                            "`address1` varchar(255) DEFAULT NULL, "
//                            "`address2` varchar(255) DEFAULT NULL, "
//                            "`city` varchar(100) DEFAULT NULL, "
//                            "`state` varchar(100) DEFAULT NULL, "
//                            "`country` varchar(100) DEFAULT NULL, "
//                            "`pincode` varchar(10) DEFAULT NULL, "
//                            "`phone1` varchar(20) DEFAULT NULL, "
//                            "`phone2` varchar(20) DEFAULT NULL, "
//                            "`mobile1` varchar(20) DEFAULT NULL, "
//                            "`mobile2` varchar(20) DEFAULT NULL, "
//                            "`email` varchar(80) DEFAULT NULL, "
//                            "`website` varchar(80) DEFAULT NULL, "
//                            "`notes` text, "
//                            "`status` CHAR(1) NOT NULL DEFAULT 'A', "
//                            "`createdDate` datetime DEFAULT NULL, "
//                            "`modifiedDate` varchar(45) DEFAULT NULL, "
//                            "`modifiedBy` int(11) DEFAULT NULL "
//                          ")");

//    //                products table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `products` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`code` varchar(100) NOT NULL, "
//                            "`name` varchar(200) NOT NULL, "
//                            "`unit` varchar(100) NOT NULL, "
//                            "`category_id` int(11) NOT NULL, "
//                            "`mrp` double NOT NULL, "
//                            "`sprice` double NOT NULL, "
//                            "`wholeSalePrice` double NOT NULL, "
//                            "`status` CHAR(1) NOT NULL DEFAULT 'A', "
//                            "`createdDate` datetime DEFAULT NULL, "
//                            "`modifiedDate` datetime DEFAULT NULL, "
//                            "`modifiedBy` int(11) DEFAULT NULL "
//                          ")");

//    //                transactions table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `transactions` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`bill_id` int(11) NOT NULL, "
//                            "`customer_id` int(11) NOT NULL, "
//                            "`paidAmount` double NOT NULL DEFAULT '0', "
//                            "`paidOn` datetime NOT NULL DEFAULT '0000-00-00 00:00:00', "
//                            "`paidBy` varchar(150) DEFAULT NULL, "
//                            "`mode` varchar(45) NOT NULL, "
//                            "`status` CHAR(1) NOT NULL DEFAULT 'A', "
//                            "`createdDate` datetime DEFAULT NULL, "
//                            "`modifiedDate` datetime DEFAULT NULL, "
//                            "`modifiedBy` int(11) DEFAULT NULL "
//                          ")");

//    //                user table creation
//                    db.exec("CREATE TABLE IF NOT EXISTS `users` ( "
//                            "`id` INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
//                            "`username` varchar(100) NOT NULL, "
//                            "`password` varchar(60) NOT NULL, "
//                            "`createdDate` datetime DEFAULT NULL, "
//                            "`modifiedDate` datetime DEFAULT NULL, "
//                            "`modifiedBy` int(11) DEFAULT '0', "
//                            "`status` CHAR(1) NOT NULL DEFAULT 'N', "
//                            "`rememberMe` CHAR(1) DEFAULT 'N' "
//                          ")");

////                    default user creation
////                    db.exec("INSERT INTO `users` (`username`, `password`, `createdDate`, `modifiedDate`, `modifiedBy`, `status`) "
////                            "VALUES ('admin', 'admin', '', '', '', 'A');");
}

/*****************************************************************************
 * category.cpp
 *
 * Created: 17/04/2014 by manikk
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
 * Manikk <manikk.h@gmail.com>
 *****************************************************************************/

#include "category.h"

Category::Category(QObject *parent) :
    QObject(parent)
{
}

QString Category::tableName()
{
    return "categories";
}
quint16 Category::id()
{
    return m_id;
}
QString Category::code()
{
    return m_code;
}
QString Category::name()
{
    return m_name;
}
QChar Category::status()
{
    return m_status;
}
QDateTime Category::createdDate()
{
    return m_createdDate;
}
QDateTime Category::modifiedDate()
{
    return m_modifiedDate;
}
quint16 Category::modifiedBy()
{
    return m_modifiedBy;
}
void Category::setId(quint16 id)
{
    m_id=id;
}
void Category::setCode(QString code)
{
    m_code=code;
}
void Category::setName(QString name)
{
    m_name=name;
}
void Category::setStatus(QChar status)
{
    m_status=status;
}
void Category::setCreatedDate(QDateTime createdDate)
{
    m_createdDate=createdDate;
}
void Category::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate=modifiedDate;
}
void Category::setModifiedBy(quint16 modifiedBy)
{
    m_modifiedBy=modifiedBy;
}
QList<QString> Category::findById()
{
    QSqlQuery query;
    QList record;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("angadi");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    query.prepare("SELECT * FROM categories WHERE id = :id");
    query.bindValue(":id",m_id);
    while(query.next())
    {
        record << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString() << query.value(5).toString();
    }
    db.close();
    return record;
}
Category Category::findByCode()
{

}
Category Category::findByAttributes()
{

}
Category Category::findAll()
{
    QSqlQuery query;
    QSqlDatabase db;
    //Category activeRecord;
    //QList<Category> records;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("angadi");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    query.prepare("SELECT * FROM categories");
    query.bindValue(":id",m_code);
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString code = query.value(1).toString();
        QString name = query.value(2).toString();
        QString status = query.value(3).toString();
        QString modifiedDate = query.value(4).toString();
        QString modifiedBy = query.value(5).toString();
    }
    db.close();
}
QList<Category> Category::findAllBySql()
{

}
QList<Category> Category::findAllByAttributes()
{

}
void Category::deleteAll()
{

}
void Category::deleteByCode()
{

}
void Category::deleteBySql()
{

}
void Category::deleteAllByAttributes()
{

}

bool Category::save()
{
    bool status;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("angadi");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE SET categories code=:code, name=:name, status=:status where id = :id ");
    query.bindValue(":id",m_id);
    query.bindValue(":code",m_code);
    query.bindValue(":name",m_name);
    query.bindValue(":status",m_status);
    if(query.exec())
        status=true ;
    else
    {
        query.prepare("INSERT INTO categories (code, name, status) "
                           "VALUES (:code,:name)");
        query.bindValue(":code",m_code);
        query.bindValue(":name",m_name);
        //query.bindValue(":status",m_status);
        if(query.exec())
            status=true ;
        else
            status=false;
    }
    db.close();
    return status;
}

bool Category::destroy()
{
    bool status;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("angadi");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE SET categories status=:status where id = :id ");
    query.bindValue(":status",m_status);
    if(query.exec())
        status=true ;
    else
        status=false;
    db.close();
    return status;
}

QList<Category> Category::search()
{

}
QList<QString> Category::getAllProducts()
{

}
QList<QString> Category::getAllBills()
{

}
QList<QString> Category::getAllTransactions()
{

}
QHash<QString,QString> Category::validate()
{

}
QHash<QString,QString> Category::errors()
{

}

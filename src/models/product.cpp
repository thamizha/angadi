/*****************************************************************************
 * product.cpp
 *
 * Created: 19/04/2014 by vijay
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
 * gvijaydhanasekaran <vijay.kuruntham@gmail.com>
 *****************************************************************************/

#include "product.h"

Product::Product(QObject *parent) :
    QObject(parent)
{
}

QString Product::tableName()
{
    return "products";
}

quint16 Product::id()
{
    return m_id;
}

QString Product::code()
{
    return m_code;
}
QString Product::name()
{
    return m_name;
}

quint16 Product::categoryId()
{
    return m_categoryId;
}
QString Product::manufacturer()
{
    return m_manufacturer;
}
QString Product::unit()
{
    return m_unit;
}
quint16 Product::mrp()
{
    return m_mrp;
}
//quint16 Product::salePrice()
quint16 Product::sprice()
{
    return m_sprice;
}
quint16 Product::wholeSalePrice()
{
    return m_wholeSalePrice;
}

QChar Product::status()
{
    return m_status;
}
QDateTime Product::createdDate()
{
    return m_createdDate;
}
QDateTime Product::modifiedDate()
{
    return m_modifiedDate;
}
quint16 Product::modifiedBy()
{
    return m_modifiedBy;
}

//******************************************************************

void Product::setId(quint16 id)
{
    m_id=id;
}
void Product::setCode(QString code)
{
    m_code=code;
}
void Product::setName(QString name)
{
    m_name=name;
}

void Product::setCategoryId(quint16 categoryId)
{
    m_categoryId=categoryId;
}

void Product::setManufacturer(QString manufacturer)
{
    m_manufacturer=manufacturer;
}

void Product::setUnit(QString unit)
{
    m_unit=unit;
}

void Product::setMrp(quint16 mrp)
{
    m_mrp=mrp;
}

void Product::setSprice(quint16 sprice)
{
    m_sprice=sprice;
}


void Product::setWholeSalePrice(quint16 wholeSalePrice)
{
    m_wholeSalePrice=wholeSalePrice;
}

void Product::setStatus(QChar status)
{
    m_status=status;
}
void Product::setCreatedDate(QDateTime createdDate)
{
    m_createdDate=createdDate;
}
void Product::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate=modifiedDate;
}
void Product::setModifiedBy(quint16 modifiedBy)
{
    m_modifiedBy=modifiedBy;
}
//******************************************************************

bool Product::save()
{
    Connection dbcn;
    bool status;
    QSqlQuery query;
    query.prepare("INSERT INTO products (code, name, unit, categoryId, manufacturer, mrp, sprice, wholeSalePrice) "
                       "VALUES (:code,:name,:unit,:categoryId,:manufacturer,:mrp,:sprice,:wholeSalePrice)");

    query.bindValue(":code",m_code);
    query.bindValue(":name",m_name);
    query.bindValue(":categoryId",m_categoryId);
    query.bindValue(":manufacturer",m_manufacturer);
    query.bindValue(":unit",m_unit);
    query.bindValue(":mrp",m_mrp);
    query.bindValue(":sprice",m_sprice);
    query.bindValue(":wholeSalePrice",m_wholeSalePrice);

    if(query.exec())
        status=true ;
    else
        status=false;
    qDebug()<<status;
    qDebug() << query.lastError();
    return status;
}








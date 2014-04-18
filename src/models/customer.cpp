/*****************************************************************************
 * customer.cpp
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
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#include "customer.h"

Customer::Customer(QObject *parent) :
    QObject(parent)
{
}

quint16 Customer::id()
{
    return m_id;
}

QString Customer::code()
{
    return m_code;
}

QString Customer::name()
{
    return m_name;
}

QString Customer::type()
{
    return m_type;
}

quint16 Customer::creditLimit()
{
    return m_creditLimit;
}

QString Customer::contactPerson()
{
    return m_contactPerson;
}

QString Customer::address1()
{
    return m_address1;
}

QString Customer::address2()
{
    return m_address2;
}

QString Customer::city()
{
    return m_city;
}

QString Customer::state()
{
    return m_state;
}

QString Customer::country()
{
    return m_country;
}

QString Customer::pincode()
{
    return m_pincode;
}

QString Customer::phone1()
{
    return m_phone1;
}

QString Customer::phone2()
{
    return m_phone2;
}

QString Customer::mobile1()
{
    return m_mobile1;
}

QString Customer::mobile2()
{
    return m_mobile2;
}

QString Customer::email()
{
    return m_email;
}

QString Customer::website()
{
    return m_website;
}

QString Customer::notes()
{
    return m_notes;
}

QChar Customer::status()
{
    return m_status;
}

QDateTime Customer::createdDate()
{
    return m_createdDate;
}

QDateTime Customer::modifiedDate()
{
    return m_modifiedDate;
}

quint16 Customer::modifiedBy()
{
    return m_modifiedBy;
}

void Customer::setId(quint16 id)
{
    m_id = id;
}

void Customer::setCode(QString code)
{
    m_code = code;
}

void Customer::setName(QString name)
{
    m_name = name;
}

void Customer::setType(QString type)
{
    m_type = type;
}

void Customer::setCreditLimit(quint16 creditLimit)
{
    m_creditLimit = creditLimit;
}

void Customer::setContactPerson(QString contactPerson)
{
    m_contactPerson = contactPerson;
}

void Customer::setAddress1(QString address1)
{
    m_address1 = address1;
}

void Customer::setAddress2(QString address2)
{
    m_address2 = address2;
}

void Customer::setCity(QString city)
{
    m_city = city;
}

void Customer::setState(QString state)
{
    m_state = state;
}

void Customer::setCountry(QString country)
{
    m_country = country;
}

void Customer::setPincode(QString pincode)
{
    m_pincode = pincode;
}

void Customer::setPhone1(QString phone1)
{
    m_phone1 = phone1;
}

void Customer::setPhone2(QString phone2)
{
    m_phone2 = phone2;
}

void Customer::setMobile1(QString mobile1)
{
    m_mobile1 = mobile1;
}

void Customer::setMobile2(QString mobile2)
{
    m_mobile2 = mobile2;
}

void Customer::setEmail(QString email)
{
    m_email = email;
}

void Customer::setWebsite(QString website)
{
    m_website = website;
}

void Customer::setNotes(QString notes)
{
    m_notes = notes;
}

void Customer::setStatus(QChar status)
{
    m_status = status;
}

void Customer::setCreatedDate(QDateTime createdDate)
{
    m_createdDate = createdDate;
}

void Customer::setModifiedDate(QDateTime modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

void Customer::setModifiedBy(quint16 modifiedBy)
{
    m_modifiedBy = modifiedBy;
}

/*Customer Customer::findById(){}
Customer Customer::findByCode(){}
Customer Customer::findByAttributes(){}

QList<Customer> Customer::findAll(){}
QList<Customer> Customer::findAllBySql(){}
QList<Customer> Customer::findAllByAttributes(){}

void Customer::deleteAll(){}
void Customer::deleteByCode(){}
void Customer::deleteBySql(){}
void Customer::deleteAllByAttributes(){}*/

bool Customer::save()
{
    Connection dbcn;
    QSqlQuery query;
    bool status = false;

    query.prepare("INSERT INTO customers (code, name, type, creditLimit, contactPerson, address1, address2, city, state, "
                  "country, pincode, phone1, phone2, mobile1, mobile2, email, website, notes) "
                  "VALUES (:code, :name, :type, :creditLimit, :contactPerson, :address1, :address2, :city, :state, "
                  ":country, :pincode, :phone1, :phone2, :mobile1, :mobile2, :email, :website, :notes)");
    query.bindValue(":code",m_code);
    query.bindValue(":name",m_name);
    query.bindValue(":type",m_type);
    query.bindValue(":creditLimit",m_creditLimit);
    query.bindValue(":contactPerson",m_contactPerson);
    query.bindValue(":address1",m_address1);
    query.bindValue(":address2",m_address2);
    query.bindValue(":city",m_city);
    query.bindValue(":state",m_state);
    query.bindValue(":country",m_country);
    query.bindValue(":pincode",m_pincode);
    query.bindValue(":phone1",m_phone1);
    query.bindValue(":phone2",m_phone2);
    query.bindValue(":mobile1",m_mobile1);
    query.bindValue(":mobile2",m_mobile2);
    query.bindValue(":email",m_email);
    query.bindValue(":website",m_website);
    query.bindValue(":notes",m_notes);

    if(query.exec())
        status=true ;
    else
        status=false;

    qDebug() << query.lastError();

    return status;
}

/*bool Customer::destroy(){}

QList<Customer> Customer::search(){}

QList<QString> Customer::getAllCustomers(){}

QHash<QString,QString> Customer::validate(){}*/
//QHash<QString,QString> Customer::errors(){}

/*****************************************************************************
 * customer.h
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

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <connection.h>

class Customer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 id READ id WRITE setId)
    Q_PROPERTY(QString code READ code WRITE setCode)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(quint16 creditLimit READ creditLimit WRITE setCreditLimit)
    Q_PROPERTY(QString contactPerson READ contactPerson WRITE setContactPerson)
    Q_PROPERTY(QString address1 READ address1 WRITE setAddress1)
    Q_PROPERTY(QString address2 READ address2 WRITE setAddress2)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString state READ state WRITE setState)
    Q_PROPERTY(QString country READ country WRITE setCountry)
    Q_PROPERTY(QString pincode READ pincode WRITE setPincode)
    Q_PROPERTY(QString phone1 READ phone1 WRITE setPhone1)
    Q_PROPERTY(QString phone2 READ phone2 WRITE setPhone2)
    Q_PROPERTY(QString mobile1 READ mobile1 WRITE setMobile1)
    Q_PROPERTY(QString mobile2 READ mobile2 WRITE setMobile2)
    Q_PROPERTY(QString email READ email WRITE setEmail)
    Q_PROPERTY(QString website READ website WRITE setWebsite)
    Q_PROPERTY(QString notes READ notes WRITE setNotes)
    Q_PROPERTY(QChar status READ status WRITE setStatus)
    Q_PROPERTY(QDateTime createdDate READ createdDate WRITE setCreatedDate)
    Q_PROPERTY(quint16 modifiedBy READ modifiedBy WRITE setModifiedBy)
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)

public:
    explicit Customer(QObject *parent = 0);

    quint16 id();
    QString code();
    QString name();
    QString type();
    quint16 creditLimit();
    QString contactPerson();
    QString address1();
    QString address2();
    QString city();
    QString state();
    QString country();
    QString pincode();
    QString phone1();
    QString phone2();
    QString mobile1();
    QString mobile2();
    QString email();
    QString website();
    QString notes();
    QChar status();
    QDateTime createdDate();
    QDateTime modifiedDate();
    quint16 modifiedBy();

    void setId(quint16 id);
    void setCode(QString code);
    void setName(QString);
    void setType(QString type);
    void setCreditLimit(quint16 creditLimit);
    void setContactPerson(QString contactPerson);
    void setAddress1(QString address1);
    void setAddress2(QString address2);
    void setCity(QString city);
    void setState(QString state);
    void setCountry(QString country);
    void setPincode(QString pincode);
    void setPhone1(QString phone1);
    void setPhone2(QString phone2);
    void setMobile1(QString mobile1);
    void setMobile2(QString mobile2);
    void setEmail(QString email);
    void setWebsite(QString website);
    void setNotes(QString notes);
    void setStatus(QChar status);
    void setCreatedDate(QDateTime createdDate);
    void setModifiedDate(QDateTime modifiedDate);
    void setModifiedBy(quint16 modifiedBy);

    /*Customer findById();
    Customer findByCode();
    Customer findByAttributes();

    QList<Customer> findAll();
    QList<Customer> findAllBySql();
    QList<Customer> findAllByAttributes();

    void deleteAll();
    void deleteByCode();
    void deleteBySql();
    void deleteAllByAttributes();*/

    bool save();
    /*bool destroy();

    QList<Customer> search();

    QList<QString> getAllCustomers();

    QHash<QString,QString> validate();
    QHash<QString,QString> errors();*/

signals:

public slots:

private:
    quint16 m_id;
    QString m_code;
    QString m_name;
    QString m_type;
    quint16 m_creditLimit;
    QString m_contactPerson;
    QString m_address1;
    QString m_address2;
    QString m_city;
    QString m_state;
    QString m_country;
    QString m_pincode;
    QString m_phone1;
    QString m_phone2;
    QString m_mobile1;
    QString m_mobile2;
    QString m_email;
    QString m_website;
    QString m_notes;
    QChar m_status;
    QDateTime m_createdDate;
    QDateTime m_modifiedDate;
    quint16 m_modifiedBy;

    //QHash<QString,QString> errors;

};

#endif // CUSTOMER_H

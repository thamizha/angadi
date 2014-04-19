/*****************************************************************************
 * product.h
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
 *
 *****************************************************************************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>
#include <QDateTime>

#include "connection.h"

class Product : public QObject
{
    Q_OBJECT


    Q_PROPERTY(quint16 id READ id WRITE setId)
    Q_PROPERTY(QString code READ code WRITE setCode)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(quint16 categoryId READ categoryId WRITE setCategoryId)
    Q_PROPERTY(QString manufacturer READ manufacturer WRITE setManufacturer)
    Q_PROPERTY(QString unit READ unit WRITE setUnit)
    Q_PROPERTY(quint16 mrp READ mrp WRITE setMrp)
    Q_PROPERTY(quint16 sprice READ sprice WRITE setSprice)
    Q_PROPERTY(quint16 wholeSalePrice READ wholeSalePrice WRITE setWholeSalePrice)

    Q_PROPERTY(QChar status READ status WRITE setStatus)
    Q_PROPERTY(QDateTime createdDate READ createdDate WRITE setCreatedDate)
    Q_PROPERTY(quint16 modifiedBy READ modifiedBy WRITE setModifiedBy)
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)


public:
    explicit Product(QObject *parent = 0);

    QString tableName();
    quint16 id();
    //Form data
    QString code();
    QString name();
    quint16 categoryId();
    QString manufacturer();\
    QString unit();
    quint16 mrp();
    quint16 sprice();
    quint16 wholeSalePrice();
    //--
    QChar status();
    QDateTime createdDate();
    QDateTime modifiedDate();
    quint16 modifiedBy();

    void setId(quint16 id);
    void setCode(QString code);
    void setName(QString name);
    void setCategoryId(quint16 categoryId);
    void setManufacturer(QString manufacturer);
    void setUnit(QString unit);
    void setMrp(quint16 mrp);
    void setSprice(quint16 sprice);
    void setWholeSalePrice(quint16 wholeSalePrice);

    void setStatus(QChar status);
    void setCreatedDate(QDateTime createdDate);
    void setModifiedDate(QDateTime modifiedDate);
    void setModifiedBy(quint16 modifiedBy);

    bool save();

private:
    quint16 m_id;
    QString m_code;
    QString m_name;
    quint16 m_categoryId;
    QString m_manufacturer;
    QString m_unit;
    quint16 m_mrp;
    quint16 m_sprice;
    quint16 m_wholeSalePrice;

    QChar m_status;
    QDateTime m_createdDate;
    QDateTime m_modifiedDate;
    quint16 m_modifiedBy;

signals:

public slots:

};

#endif // PRODUCT_H

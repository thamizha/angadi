/*****************************************************************************
 * connection.h
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

#ifndef CONNECTION_H
#define CONNECTION_H
//#include "dbsettings.h"

#include <QObject>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <QHash>
#include <QDateTime>
#include <QList>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QSqlError>
#include <QtSql/QtSql>

class Connection : public QObject
{
    Q_OBJECT
    QString hostName, username, password;
    qint8 port;
public:
    explicit Connection(QObject *parent = 0);
    QSqlDatabase db;
    ~Connection();
//    DBSettings *dbsettings;
//    void checkDBOpen();
signals:

public slots:

private:
    void createSqliteTables();
    /*bool checkConnectionParams();
    void createAndOpenDb();
    void closeDb();
    bool openConnection(QString dbName);
    bool checkMysqlUsername();*/
};

#endif // CONNECTION_H

/*****************************************************************************
 * categoriesmodel.h
 *
 * Created: 22/04/2014 by manikk
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

#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H

#include <QSqlTableModel>

class CategoriesModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CategoriesModel(QObject *parent = 0);
    ~CategoriesModel();

signals:

public slots:

private:

};

#endif // CATEGORIESMODEL_H

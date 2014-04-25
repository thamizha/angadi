/*****************************************************************************
 * lssbar.cpp
 *
 * Created: 19/04/2014 by selvam
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

#include "lssbar.h"
#include "connection.h"
#include <QHeaderView>

Lssbar::Lssbar(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

void Lssbar::setupUi()
{
    QVBoxLayout *vBox = new QVBoxLayout;
    tableView = new QTableView;
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    vBox->addWidget(tableView);
    this->setLayout(vBox);

    connect(this->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(edit(QModelIndex)));
}

void Lssbar::setModel(QSqlTableModel *tableModel){

    //tableModel->select();
    tableView->setModel(tableModel);

    //set all columns hidden
    for(int i=0;i<tableModel->columnCount();i++){
        tableView->setColumnHidden(i,true);
    }

    if(tableModel->tableName() == "categories" || tableModel->tableName() == "test"){
        int codeIndex = tableModel->fieldIndex("code");
        int nameIndex = tableModel->fieldIndex("name");
        tableView->setColumnHidden(codeIndex,false);
        tableView->setColumnHidden(nameIndex,false);

    }else if(tableModel->tableName() == "products"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);
    }else if(tableModel->tableName() == "customers"){

    }
}

void Lssbar::edit(QModelIndex a)
{
    qDebug() << a;
}

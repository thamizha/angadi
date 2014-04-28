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
#include "categoryform.h"
#include <QHeaderView>
#include <QEvent>
#include <QKeyEvent>

Lssbar::Lssbar(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

void Lssbar::setupUi()
{
    QVBoxLayout *vBox = new QVBoxLayout;

    lineEditSearch= new QLineEdit(this);
    lineEditSearch->installEventFilter(this);
    //QLineEdit *lineEditName= new QLineEdit(this);

    tableView = new QTableView;
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    vBox->addWidget(lineEditSearch);
    //vBox->addWidget(lineEditName);
    vBox->addWidget(tableView);

    this->setLayout(vBox);

    connect(lineEditSearch,SIGNAL(textChanged(QString)),this,SLOT(search(QString)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
    connect(lineEditSearch,SIGNAL(returnPressed()),this,SLOT(returnKeyPressed()));
}

void Lssbar::setModel(QSqlTableModel *tableModel)
{
    tableView->setModel(tableModel);

    //set all columns hidden
    for(int i=0;i<tableModel->columnCount();i++){
        tableView->setColumnHidden(i,true);
    }

    if(tableModel->tableName() == "categories"){
        int codeIndex = tableModel->fieldIndex("code");
        int nameIndex = tableModel->fieldIndex("name");
        tableView->setColumnHidden(codeIndex,false);
        tableView->setColumnHidden(nameIndex,false);

    }else if(tableModel->tableName() == "products"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);

    }else if(tableModel->tableName() == "customers"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);

    }
}

void Lssbar::setFilterSelect(QModelIndex index, int update)
{
    tableView->clearSelection();
    indexOffset=update;
    if (index.isValid()) {
        tableView->setColumnHidden(0, false);
        tableView->selectionModel()->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        tableView->scrollTo(index, QAbstractItemView::EnsureVisible);
        tableView->setColumnHidden(0, true);
        tableView->setCurrentIndex(index);
    }


    /*//set all columns hidden
    for(int i=0;i<tableModel->columnCount();i++){
        tableView->setColumnHidden(i,true);
    }

    if(tableModel->tableName() == "categories"){
        int codeIndex = tableModel->fieldIndex("code");
        int nameIndex = tableModel->fieldIndex("name");
        tableView->setColumnHidden(codeIndex,false);
        tableView->setColumnHidden(nameIndex,false);

    }else if(tableModel->tableName() == "products"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);

    }else if(tableModel->tableName() == "customers"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);

    }*/
}

void Lssbar::doubleClicked(QModelIndex index)
{
    emit signalEdit(index);
}

void Lssbar::search(QString value)
{
    emit signalSearch(value);
}

bool Lssbar::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == lineEditSearch)
        {
            if (event->type() == QEvent::KeyPress)
            {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                if (keyEvent->key() == Qt::Key_Up)
                {
                    indexOffset=indexOffset-1;
                    emit signalMoveUpDown(indexOffset);
                    return true;
                }
                else if(keyEvent->key() == Qt::Key_Down)
                {
                    indexOffset=indexOffset+1;
                    emit signalMoveUpDown(indexOffset);
                    return true;
                }
            }
            return false;
        }
        return Lssbar::eventFilter(obj, event);
}

void Lssbar::returnKeyPressed()
{
    QModelIndex index = tableView->currentIndex();
    emit signalEdit(index);
}

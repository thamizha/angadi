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
#include <QSqlRelationalDelegate>

Lssbar::Lssbar(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

void Lssbar::setupUi()
{
    QVBoxLayout *vBox = new QVBoxLayout;

    // new lineedit intialization for search bar
    lineEditSearch = new QLineEdit(this);
    lineEditSearch->installEventFilter(this);
    //QLineEdit *lineEditName= new QLineEdit(this);

    tableView = new QTableView;
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // adding lineedit widget to the right dock
    vBox->addWidget(lineEditSearch);
    //vBox->addWidget(lineEditName);
    vBox->addWidget(tableView);

    this->setLayout(vBox);

    connect(lineEditSearch,SIGNAL(textChanged(QString)),this,SLOT(search(QString)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
    connect(tableView,SIGNAL(activated(QModelIndex)),this,SLOT(doubleClicked(QModelIndex)));
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
        tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));

        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);

    }else if(tableModel->tableName() == "customers"){
        tableView->setColumnHidden(tableModel->fieldIndex("code"),false);
        tableView->setColumnHidden(tableModel->fieldIndex("name"),false);
    }
}

void Lssbar::setFilterSelect(QModelIndex index, int update)
{
    tableView->clearSelection();// clear the previous selection
    indexOffset=update; //update the indexOffset value
    if (index.isValid()) {
        tableView->setColumnHidden(0, false); // to unhide the hidden primary key column
        tableView->selectionModel()->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows); //select the row given by index
        tableView->scrollTo(index, QAbstractItemView::EnsureVisible); //scroll to that row so that its visible
        tableView->setColumnHidden(0, true); // hide the primary key column
        tableView->setCurrentIndex(index); //set the current index of the table view to the current index
    }
}

//to emit the double clicked on the table view row signal
void Lssbar::doubleClicked(QModelIndex index)
{
    emit signalEdit(index);
}

//to emit the search signal for the typed value on the lineeditsearch
void Lssbar::search(QString value)
{
    emit signalSearch(value);
}

//event filter to listen to the up/down arrow key on the lineedit search
bool Lssbar::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == lineEditSearch) //to check if the obj is lineedit search
    {
        if (event->type() == QEvent::KeyPress) //to check if the event is keypress event
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event); //if it is keypress event in lineedit search assign a new keyevent variable
            if (keyEvent->key() == Qt::Key_Up) //to check if the keyevent is up
            {
                indexOffset=indexOffset-1; //offset the index by -1
                emit signalMoveUpDown(indexOffset); //emit the signal moveup/down
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Down) // to check if the keyevent is down arrow
            {
                indexOffset=indexOffset+1; //offset the index by +1
                emit signalMoveUpDown(indexOffset); //emit the signal moveup/down
                return true;
            }
        }
        return false;
    }
    return Lssbar::eventFilter(obj, event);
}

// to emit the return key press signal on the lineedit search so that the selected index data is moved to the form
void Lssbar::returnKeyPressed()
{
    QModelIndex index = tableView->currentIndex(); //get the current index of the table view
    emit signalEdit(index); //emit the signal edit so that the data is moved to the form
}

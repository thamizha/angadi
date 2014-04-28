/*****************************************************************************
 * lssbar.h
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
 *
 *****************************************************************************/

#ifndef LSSBAR_H
#define LSSBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QDebug>
#include <QLineEdit>
#include <QSortFilterProxyModel>

class Lssbar : public QWidget
{
    Q_OBJECT
public:
    explicit Lssbar(QWidget *parent = 0);
    QTableView *tableView;
    QLineEdit *lineEditSearch;
    int indexOffset = 0;

signals:
    void signalEdit(QModelIndex);
    void signalSearch(QString value);
    void signalMoveUpDown(int);

public slots:
    void setModel(QSqlTableModel *tableModel);
    void setFilterSelect(QModelIndex index,int update);

private:


private slots:
    void setupUi();
    void doubleClicked(QModelIndex index);
    void search(QString value);
    bool eventFilter(QObject *obj, QEvent *event);
    void returnKeyPressed();
};

#endif // LSSBAR_H

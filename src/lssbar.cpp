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
#include <QHeaderView>

Lssbar::Lssbar(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

void Lssbar::setupUi()
{
    QVBoxLayout *vBox = new QVBoxLayout;
    tableWidget = new QTableWidget;
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);

    vBox->addWidget(tableWidget);
    this->setLayout(vBox);
}

/*void Lssbar::populate()
{
    Category *category = new Category;
    QSqlTableModel *model = category->findAll();

    tableWidget->setRowCount(model->rowCount());

    for(int i=0; i<model->rowCount(); i++){
        QSqlRecord record = model->record(i);

        QTableWidgetItem *code = new QTableWidgetItem(record.value("code").toString());
        QTableWidgetItem *name = new QTableWidgetItem(record.value("name").toString());

        qDebug() << record.value("name").toString();

        tableWidget->setItem(i,0,code);
        tableWidget->setItem(i,1,name);
    }
}*/


void Lssbar::populate(QString data,quint16 totalRecords)
{
    tableWidget->setRowCount(totalRecords);
    qDebug() << data<<endl;
    QStringList list = data.split("|");
    qDebug() << list.size();
    for (int i = 0; i < list.size(); i++)
    {
       qDebug() << list[i]<< endl;
       QStringList datas = list[i].split("~");
           for (int j=0;j<datas.size();j++)
           {
               QTableWidgetItem *code = new QTableWidgetItem(datas[j]);
               tableWidget->setItem(j,i,code);
               qDebug() << datas[j];
           }
    }
}




/*****************************************************************************
 * periodwisesalesform.cpp
 *
 * Created: 14/05/2014 by selvam
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

#include "periodwisesalesform.h"
#include "ui_periodwisesalesform.h"

PeriodWiseSalesForm::PeriodWiseSalesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeriodWiseSalesForm)
{
    ui->setupUi(this);

//    QDate date = QDate::currentDate();
//    ui->dateEditFrom->setDate(date);
    //ui->dateEditFrom->setSelectedSection(QDateEdit::NoSection);
    //ui->dateEditTo->setDate(date);
    //ui->dateEditTo->setSelectedSection(QDateEdit::NoSection);

    fromFilter = "2014-01-01";
    toFilter = "2015-01-01";
    invoiceNoFilter = "";
    totalFilter = "";
    customerFilter = "";

    //filter = "bill.status = 'A' and invoiceNo = "+invoiceNoFilter+" and totalAmount = "+totalFilter+" and customer_id = "+customerFilter;

    billModel = new QSqlRelationalTableModel();
    billModel->setTable("bill");
    billModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    billModel->setRelation(3, QSqlRelation("customers", "id", "name"));
    filter = "bill.status = 'A'";
    billModel->setFilter(filter);
    billModel->select();

    billProxy = new QSortFilterProxyModel;
    billProxy->setSourceModel(billModel);

    ui->tableView->setModel(billProxy);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(7,true);

    for (int i = 8; i<billProxy->columnCount(); ++i)
        ui->tableView->setColumnHidden(i,true);
}

PeriodWiseSalesForm::~PeriodWiseSalesForm()
{
    delete ui;
}

void PeriodWiseSalesForm::on_lineEditInvoiceNo_textChanged(const QString &arg1)
{
    invoiceNoFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::on_dateEditFrom_dateChanged(const QDate &date)
{
    fromFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void PeriodWiseSalesForm::on_dateEditTo_dateChanged(const QDate &date)
{
    toFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void PeriodWiseSalesForm::on_lineEditCustomer_textChanged(const QString &arg1)
{
    customerFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::on_lineEditTotal_textChanged(const QString &arg1)
{
    totalFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::setModel()
{
    //filter = "bill.status = 'A' and bill.totalAmount like '%"+totalFilter+"%'";
    filter = "bill.status = 'A' and invoiceNo like '%"+invoiceNoFilter+"%' and totalAmount like '%"+totalFilter+"%' and relTblAl_3.name like '%"+customerFilter+"%' and invoiceDate >= '"+fromFilter+"' and invoiceDate <= '"+toFilter+"'";
    billModel->setFilter(filter);
    billModel->select();
}

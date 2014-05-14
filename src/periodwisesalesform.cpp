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

    fromFilter = "0";
    toFilter = "0";
    invoiceNoFilter = "0";
    totalFilter = "0";
    customerFilter = "0";

//    filter = "paidStatus = 'U' and invoiceNo = "+invoiceNoFilter+" and totalAmount = "+totalFilter+" and customer_id = "+customerFilter;

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
    if(arg1.length() == 0)
        invoiceNoFilter = "0";
    else
        invoiceNoFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::on_dateEditFrom_dateChanged(const QDate &date)
{

}

void PeriodWiseSalesForm::on_dateEditTo_dateChanged(const QDate &date)
{

}

void PeriodWiseSalesForm::on_lineEditCustomer_textChanged(const QString &arg1)
{
    if(arg1.length() == 0)
        customerFilter = "0";
    else
        customerFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::on_lineEditTotal_textChanged(const QString &arg1)
{
    if(arg1.length() == 0)
        totalFilter = "0";
    else
        totalFilter = arg1;
    setModel();
}

void PeriodWiseSalesForm::setModel()
{
    filter = "bill.status = 'A' and bill.invoiceNo like '%"+invoiceNoFilter+"%' and bill.totalAmount like '%"+totalFilter+"%' and bill.customer_id = '%"+customerFilter+"%'";
    billModel->setFilter(filter);
    billModel->select();
}

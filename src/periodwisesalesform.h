/*****************************************************************************
 * periodwisesalesform.h
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

#ifndef PERIODWISESALESFORM_H
#define PERIODWISESALESFORM_H

#include <QWidget>
#include <QDateTime>
#include <QEvent>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class PeriodWiseSalesForm;
}

class PeriodWiseSalesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PeriodWiseSalesForm(QWidget *parent = 0);
    ~PeriodWiseSalesForm();

private:
    Ui::PeriodWiseSalesForm *ui;
    QSortFilterProxyModel *billProxy;
    QString filter;
    QString fromFilter;
    QString toFilter;
    QString invoiceNoFilter;
    QString customerFilter;
    QString totalFilter;
    QSqlRelationalTableModel *billModel;

private slots:
    void on_lineEditInvoiceNo_textChanged(const QString &arg1);

    void on_dateEditFrom_dateChanged(const QDate &date);

    void on_dateEditTo_dateChanged(const QDate &date);

    void on_lineEditCustomer_textChanged(const QString &arg1);

    void on_lineEditTotal_textChanged(const QString &arg1);

    void setModel();
};

#endif // PERIODWISESALESFORM_H

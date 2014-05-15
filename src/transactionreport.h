#ifndef TRANSACTIONREPORT_H
#define TRANSACTIONREPORT_H

#include "rightaligndelegate.h"
#include "timeeditdelegate.h"

#include <QWidget>
#include <QDateTime>
#include <QDate>
#include <QEvent>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class TransactionReport;
}

class TransactionReport : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionReport(QWidget *parent = 0);
    ~TransactionReport();

private:
    Ui::TransactionReport *ui;
    QString filter;
    QString fromFilter;
    QString toFilter;
    QString invoiceNoFilter;
    QString customerFilter;
    QString paidByFilter;
    QString paidAmountFilter;
    QSqlRelationalTableModel *transactionModel;
    QSortFilterProxyModel *transactionProxy;

private slots:
    void setModel();
    void calTotal();
    void on_lineEditInvoice_textChanged(const QString &arg1);
    void on_lineEditCustomer_textChanged(const QString &arg1);
    void on_dateEditTo_dateChanged(const QDate &date);
    void on_dateEditFrom_dateChanged(const QDate &date);
    void on_lineEditPaidAmount_textChanged(const QString &arg1);
    void on_lineEditPaidBy_textChanged(const QString &arg1);
};

#endif // TRANSACTIONREPORT_H

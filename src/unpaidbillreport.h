#ifndef UNPAIDBILLREPORT_H
#define UNPAIDBILLREPORT_H

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
#include <QDir>

namespace Ui {
class UnpaidBillReport;
}

class UnpaidBillReport : public QWidget
{
    Q_OBJECT

public:
    explicit UnpaidBillReport(QWidget *parent = 0);
    ~UnpaidBillReport();
    void settranslate();

private:
    Ui::UnpaidBillReport *ui;
    QSortFilterProxyModel *billProxy;
    QString filter;
    QString fromFilter;
    QString toFilter;
    QString invoiceNoFilter;
    QString customerFilter;
    QString totalFilter;
    QString balanceFilter;
    QSqlRelationalTableModel *billModel;

private slots:

    void on_dateEditFrom_dateChanged(const QDate &date);
    void on_dateEditTo_dateChanged(const QDate &date);
    void on_lineEditInvoice_textChanged(const QString &arg1);
    void on_lineEditCustomer_textChanged(const QString &arg1);
    void on_lineEditTotal_textChanged(const QString &arg1);
    void on_lineEditBalance_textChanged(const QString &arg1);
    void setModel();
    void calTotal();
    void setLanguage();
};

#endif // UNPAIDBILLREPORT_H

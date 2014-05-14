#ifndef UNPAIDBILLREPORT_H
#define UNPAIDBILLREPORT_H

#include <QWidget>
#include <QDateTime>
#include <QEvent>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class UnpaidBillReport;
}

class UnpaidBillReport : public QWidget
{
    Q_OBJECT

public:
    explicit UnpaidBillReport(QWidget *parent = 0);
    ~UnpaidBillReport();

private:
    Ui::UnpaidBillReport *ui;
    QSortFilterProxyModel *billProxy;
    QString filter;
    QSqlRelationalTableModel *billModel;

private slots:

};

#endif // UNPAIDBILLREPORT_H

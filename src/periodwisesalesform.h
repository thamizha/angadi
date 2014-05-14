#ifndef PERIODWISESALESFORM_H
#define PERIODWISESALESFORM_H

#include <QWidget>
#include <QDateTime>
#include <QEvent>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>

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

    QString filter;
    QSqlRelationalTableModel *billItemModel;
    QSortFilterProxyModel *billItemModelProxy;
    QSqlQueryModel *model;

private slots:

};

#endif // PERIODWISESALESFORM_H

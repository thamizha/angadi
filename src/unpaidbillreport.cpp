#include "unpaidbillreport.h"
#include "ui_unpaidbillreport.h"
#include <QSqlError>

UnpaidBillReport::UnpaidBillReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnpaidBillReport)
{
    ui->setupUi(this);

    fromFilter = "0";
    toFilter = "0";
    invoiceNoFilter = "0";
    totalFilter = "0";
    customerFilter = "0";
    balanceFilter = "0";

    filter = "paidStatus = 'U' and invoiceNo = "+invoiceNoFilter+" and totalAmount = "+totalFilter+" and customer_id = "+customerFilter+" and dueAmount = "+balanceFilter;

    billModel = new QSqlRelationalTableModel();
    billModel->setTable("bill");
    billModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    billModel->setRelation(3, QSqlRelation("customers", "id", "name"));
    filter = "paidStatus = 'U'";
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
    for (int i = 8; i<billProxy->columnCount(); ++i)
        ui->tableView->setColumnHidden(i,true);
}

UnpaidBillReport::~UnpaidBillReport()
{
    delete ui;
}


void UnpaidBillReport::on_dateEditFrom_userDateChanged(const QDate &date)
{

}

void UnpaidBillReport::on_dateEditTo_userDateChanged(const QDate &date)
{

}

void UnpaidBillReport::on_lineEditInvoice_textChanged(const QString &arg1)
{

}

void UnpaidBillReport::on_lineEditCustomer_textChanged(const QString &arg1)
{

}

void UnpaidBillReport::on_lineEditTotal_textChanged(const QString &arg1)
{
    if(arg1.length() == 0)
        totalFilter = "0";
    else
        totalFilter = arg1;
    setModel();
}

void UnpaidBillReport::on_lineEditBalance_textChanged(const QString &arg1)
{
    if(arg1.length() == 0)
        balanceFilter = "0";
    else
        balanceFilter = arg1;
    setModel();
}

void UnpaidBillReport::setModel()
{
    filter = "paidStatus = 'U' and invoiceNo >= "+invoiceNoFilter+" and totalAmount >= "+totalFilter+" and customer_id >= "+customerFilter+" and dueAmount >= "+balanceFilter;
    billModel->setFilter(filter);
    billModel->select();
}

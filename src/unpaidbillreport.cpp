#include "unpaidbillreport.h"
#include "ui_unpaidbillreport.h"
#include <QSqlError>

UnpaidBillReport::UnpaidBillReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnpaidBillReport)
{
    ui->setupUi(this);

    fromFilter = "2014-01-01";
    toFilter = "2015-01-01";
    invoiceNoFilter = "";
    totalFilter = "";
    customerFilter = "";
    balanceFilter = "";

    filter = "paidStatus = 'U' and invoiceNo = "+invoiceNoFilter+" and totalAmount = "+totalFilter+" and customer_id = '"+customerFilter+" and dueAmount = "+balanceFilter;

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
    calTotal();
}

UnpaidBillReport::~UnpaidBillReport()
{
    delete ui;
}


void UnpaidBillReport::on_dateEditFrom_dateChanged(const QDate &date)
{
    fromFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void UnpaidBillReport::on_dateEditTo_dateChanged(const QDate &date)
{
    toFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void UnpaidBillReport::on_lineEditInvoice_textChanged(const QString &arg1)
{
    invoiceNoFilter = arg1;
    setModel();
}

void UnpaidBillReport::on_lineEditCustomer_textChanged(const QString &arg1)
{
    customerFilter = arg1;
    setModel();
}

void UnpaidBillReport::on_lineEditTotal_textChanged(const QString &arg1)
{
    totalFilter = arg1;
    setModel();
}

void UnpaidBillReport::on_lineEditBalance_textChanged(const QString &arg1)
{
    balanceFilter = arg1;
    setModel();
}

void UnpaidBillReport::setModel()
{
    filter = "paidStatus = 'U' and invoiceNo like '%"+invoiceNoFilter+"%' and totalAmount like '%"+totalFilter+"%' and relTblAl_3.name = '"+customerFilter+"' and dueAmount like '%"+balanceFilter+"%' and invoiceDate >= '"+fromFilter+"' and invoiceDate <= '"+toFilter+"'";
    billModel->setFilter(filter);
    billModel->select();
    calTotal();
}

void UnpaidBillReport::calTotal()
{
    int totalBalance = 0;
    QSqlRecord billRecord;
    for(int i = 0; i< billModel->rowCount(); ++i){
        billRecord = billModel->record(i);
        totalBalance=totalBalance+billRecord.value(7).toInt();
    }
    ui->lineEditTotalBalance->setText(QString::number(totalBalance));
}

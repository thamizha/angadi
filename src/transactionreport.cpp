#include "transactionreport.h"
#include "ui_transactionreport.h"
#include <QSqlError>

TransactionReport::TransactionReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionReport)
{
    ui->setupUi(this);

    fromFilter = QDate::currentDate().toString("yyyy-MM-dd");
    toFilter = fromFilter;
    paidAmountFilter = "";
    customerFilter = "";
    invoiceNoFilter = "";
    paidByFilter = "";
    filter = "transactions.status = 'A'";


    transactionModel = new QSqlRelationalTableModel();
    transactionModel->setTable("transactions");
    transactionModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    transactionModel->setRelation(1, QSqlRelation("bill", "id", "invoiceNo"));
    transactionModel->setRelation(2, QSqlRelation("customers", "id", "name"));
    transactionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Invoice Number"));
    transactionModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Customer Name"));
    transactionModel->setFilter(filter);
    transactionModel->select();
    qDebug() << transactionModel->lastError();

    transactionProxy = new QSortFilterProxyModel();
    transactionProxy->setSourceModel(transactionModel);

    ui->tableView->setModel(transactionProxy);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(4,210);
    ui->tableView->setColumnWidth(3,217);
    ui->tableView->setColumnWidth(2,200);
    ui->tableView->setColumnWidth(5,200);
    ui->tableView->setColumnHidden(0,true);
    for (int i = 6; i<transactionProxy->columnCount(); ++i)
        ui->tableView->setColumnHidden(i,true);
//    ui->dateEditFrom->setDate(QDate::currentDate());
//    ui->dateEditTo->setDate(QDate::currentDate());
    ui->lineEditTotalBalance->setEnabled(false);

}

TransactionReport::~TransactionReport()
{
    delete ui;
}

void TransactionReport::setModel()
{
    filter = "transactions.status = 'A' and relTblAl_1.invoiceNo like '%"+invoiceNoFilter+"%' and paidAmount like '%"+paidAmountFilter+"%' and relTblAl_2.name like '%"+customerFilter+"%' and paidBy like '%"+paidByFilter+"%' and paidOn >= '"+fromFilter+"' and paidOn <= '"+toFilter+"'";
    transactionModel->setFilter(filter);
    transactionModel->select();
    calTotal();
}

void TransactionReport::calTotal()
{
    int totalPaid = 0;
    QSqlRecord transactionRecord;
    for(int i = 0; i< transactionModel->rowCount(); ++i){
        transactionRecord = transactionModel->record(i);
        totalPaid=totalPaid+transactionRecord.value(3).toInt();
    }
    ui->lineEditTotalBalance->setText(QString::number(totalPaid));
    ui->tableView->resizeRowsToContents();
}

void TransactionReport::on_lineEditInvoice_textChanged(const QString &arg1)
{
    invoiceNoFilter = arg1;
    setModel();
}

void TransactionReport::on_lineEditCustomer_textChanged(const QString &arg1)
{
    customerFilter = arg1;
    setModel();
}

void TransactionReport::on_dateEditTo_dateChanged(const QDate &date)
{
    toFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void TransactionReport::on_dateEditFrom_dateChanged(const QDate &date)
{
    fromFilter = date.toString("yyyy-MM-dd");
    setModel();
}

void TransactionReport::on_lineEditPaidAmount_textChanged(const QString &arg1)
{
    paidAmountFilter = arg1;
    setModel();
}

void TransactionReport::on_lineEditPaidBy_textChanged(const QString &arg1)
{
    paidByFilter = arg1;
    setModel();
}

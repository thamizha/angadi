#include "unpaidbillreport.h"
#include "ui_unpaidbillreport.h"

UnpaidBillReport::UnpaidBillReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnpaidBillReport)
{
    ui->setupUi(this);

    billModel = new QSqlRelationalTableModel();
    billModel->setTable("bill");
    billModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    billModel->setRelation(3, QSqlRelation("customers", "id", "customer_id"));
    filter = "paidStatus = U";
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
    for (int i = 0; i<billProxy->columnCount(); ++i){
        if(i==2 && i==3 && i==1 && i==6 && i==7)
            ui->tableView->setColumnHidden(i,false);
        else
            ui->tableView->setColumnHidden(i,true);
    }
}

UnpaidBillReport::~UnpaidBillReport()
{
    delete ui;
}


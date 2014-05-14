#include "periodwisesalesform.h"
#include "ui_periodwisesalesform.h"

PeriodWiseSalesForm::PeriodWiseSalesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeriodWiseSalesForm)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    ui->dateEditFromDate->setDate(date);
    ui->dateEditToDate->setDate(date);
    ui->dateEditFromDate->setSelectedSection(QDateEdit::NoSection);
    ui->dateEditToDate->setSelectedSection(QDateEdit::NoSection);

    billItemModel = new QSqlRelationalTableModel();
    billItemModel->setTable("bill_item");
    billItemModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    billItemModel->setRelation(2, QSqlRelation("products", "id", "name"));
    billItemModel->select();

    billItemModelProxy = new QSortFilterProxyModel;
    billItemModelProxy->setSourceModel(billItemModel);

//    ui->tableView->setModel(billItemModel);

//    using qsqlquerymodel
    model = new QSqlQueryModel;
    model->setQuery("Select b.invoiceNo,b.invoiceDate,p.name,p.unit,bi.quantity,bi.unitPrice,bi.total from bill b "
                    "inner join bill_item bi on bi.bill_id = b.id "
                    "inner join products p on p.id = bi.product_id "
                    "where b.invoicedate>='2014-05-12' and b.invoicedate<='2014-05-13'");
    ui->tableView->setModel(model);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();

//    for(int i=0;i<billItemModel->columnCount();i++){
//        if(i == 0 || i == 1)
//            ui->tableView->setColumnHidden(i,true);
//        else
//            ui->tableView->setColumnHidden(i,false);
//    }
}

PeriodWiseSalesForm::~PeriodWiseSalesForm()
{
    delete ui;
}


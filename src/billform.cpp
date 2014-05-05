#include "billform.h"
#include "ui_billform.h"

BillForm::BillForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillForm)
{
    ui->setupUi(this);
}

BillForm::~BillForm()
{
    delete ui;
}

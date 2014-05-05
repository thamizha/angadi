#include "logindialog.h"
#include "ui_logindialog.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QCryptographicHash>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButtonEnter_clicked()
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(ui->lineEditPassword->text().toUtf8());

    QSqlQueryModel model;
    QSqlQuery query;
    query.prepare("Select * from users where username=:username and password=:password and status = 'A'");
    query.bindValue(":username", ui->lineEditUsername->text().trimmed());
    query.bindValue(":password", hash.result().toHex());
    query.exec();
    model.setQuery(query);
    if(model.rowCount() > 0){
        emit loggedIn();
    }else{
        qDebug() << "Login Failed";
    }
}

void LoginDialog::on_pushButtonExit_clicked()
{
    emit exitApp();
}

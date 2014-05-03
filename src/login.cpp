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
//    QByteArray inputPassword = ui->lineEditPassword->text().toUtf8().left(1000);
//    QByteArray password = QString(QCryptographicHash::hash((inputPassword),QCryptographicHash::Md5)).toUtf8().left(1000);
//    qDebug() << password.toHex();
//    QSqlQueryModel model;
//    QSqlQuery query;
//    query.prepare("Select * from users where username=:username and password=:password");
//    query.bindValue(":username", ui->lineEditUsername->text().trimmed());
//    query.bindValue(":password", password);
//    query.exec();
//    model.setQuery(query);

//    if(model.rowCount() > 0){
        emit loggedIn();
//    }else{
//        qDebug() << "Login Failed";
//    }
}

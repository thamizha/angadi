#include "logindialog.h"
#include "ui_logindialog.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QCryptographicHash>
#include <QTranslator>
#include <QSettings>
#include <QDir>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setLanguage();

    QString admin = "admin";
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(admin.toUtf8());

    QSqlQueryModel model;
    QSqlQuery query;
    query.prepare("Select * from users");
    query.exec();
    model.setQuery(query);
    if(model.rowCount() <= 0){
        query.prepare("INSERT INTO `users` (`username`, `password`, `createdDate`, `modifiedDate`, `modifiedBy`, `status`) "
                      "VALUES ('admin', :password, '', '', '', 'A');");
        query.bindValue(":password", hash.result().toHex());
        query.exec();
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::settranslate()
{
    ui->retranslateUi(this);
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

void LoginDialog::setLanguage()
{
    //Language setup
    QString app_path;
    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
    QSettings settings(app_path,QSettings::NativeFormat);
    QString content = settings.value("s_language","").toString();

    if(content == "tamil_language"){
        QTranslator translator;
        translator.load("tamilLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);

     }else{
        QTranslator translator;
        translator.load("englishLanguage_la");
    //  QApplication::installTranslator(&translator);
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

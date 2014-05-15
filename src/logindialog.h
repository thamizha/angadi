#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void settranslate();
signals:
    void loggedIn();
    void exitApp();

private slots:
    void on_pushButtonEnter_clicked();
    void on_pushButtonExit_clicked();

private:
    Ui::LoginDialog *ui;
    void setLanguage();
};

#endif // LOGINDIALOG_H

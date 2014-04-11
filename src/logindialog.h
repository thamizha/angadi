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

signals:
    void loggedIn();

private slots:
    void on_pushButtonEnter_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H

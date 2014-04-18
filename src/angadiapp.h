#ifndef ANGADIAPP_H
#define ANGADIAPP_H

#include <QApplication>
#include "logindialog.h"
#include "angadimainwindow.h"

class AngadiApp : public QApplication
{
    Q_OBJECT
public:
    explicit AngadiApp(int argc, char *argv[]);
    void start();

signals:

public slots:
    void exitApp();

private :
    LoginDialog *login;
    AngadiMainWindow *angadiMainWindow;


private slots:
    void onLoggedIn();

};

#endif // ANGADIAPP_H

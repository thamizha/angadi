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

private :
    LoginDialog *login;
    AngadiMainWindow *angadiMainWindow;
    void exitApp();

private slots:
    void onLoggedIn();

};

#endif // ANGADIAPP_H

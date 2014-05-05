#include "angadiapp.h"
#include "logindialog.h"
#include "angadimainwindow.h"
#include <connection.h>

#include <QDebug>

AngadiApp::AngadiApp(int argc,char *argv[]) :
    QApplication(argc,argv)
{
    Connection dbcn;

    login = new LoginDialog();
    angadiMainWindow = new AngadiMainWindow();
}

void AngadiApp::start()
{
    connect(login,SIGNAL(loggedIn()),this,SLOT(onLoggedIn()));
    connect(login,SIGNAL(exitApp()),this,SLOT(exitApp()));
    connect(angadiMainWindow,SIGNAL(exit()),this,SLOT(exitApp()));
//    login->show();
    angadiMainWindow->showMaximized();
}


void AngadiApp::onLoggedIn()
{
    login->hide();
    angadiMainWindow->showMaximized();
}

void AngadiApp::exitApp()
{
    //qDebug() << "Exit App called";
    this->quit();
}


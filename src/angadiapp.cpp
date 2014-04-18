#include "angadiapp.h"
#include "logindialog.h"
#include "angadimainwindow.h"
#include <QDebug>

AngadiApp::AngadiApp(int argc,char *argv[]) :
    QApplication(argc,argv)
{
    login = new LoginDialog();
    angadiMainWindow = new AngadiMainWindow();
}

void AngadiApp::start()
{
    //login->show();
    //connect(login,SIGNAL(loggedIn()),this,SLOT(onLoggedIn()));
    connect(angadiMainWindow,SIGNAL(exit()),this,SLOT(exitApp()));
    angadiMainWindow->showMaximized();
}


void AngadiApp::onLoggedIn()
{
    login->hide();
    angadiMainWindow->showMaximized();
}

void AngadiApp::exitApp()
{
    qDebug() << "Exit App called";
    this->quit();
}


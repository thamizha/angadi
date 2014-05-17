#include "angadiapp.h"
#include <connection.h>
#include <QSplashScreen>

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

    QPixmap pix(":/images/icons/about_splash.png");
    QSplashScreen splash(pix);
    splash.show();

    QTime dieTime= QTime::currentTime().addSecs(3);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents,50);

    splash.hide();

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


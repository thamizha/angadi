#include <angadiapp.h>
#include <QWidget>
#include <QtWidgets>
#include <QWindow>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    AngadiApp a(argc, argv);

//    QPixmap pix(":/images/icons/about_splash.png");
//    QSplashScreen splash(pix);
//    splash.show();

//    #ifdef WIN32
//    // Windows code here
//        Sleep(5000);
//    #else
//    // UNIX code here
//        struct timespec ts = { 5000 / 1000, (5000 % 1000) * 1000 * 1000 };
//        nanosleep(&ts, NULL);
//    #endif

//    splash.hide();

    a.start();
    return a.exec();
}

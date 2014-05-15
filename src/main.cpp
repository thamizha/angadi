#include <angadiapp.h>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    AngadiApp a(argc, argv);

    QPixmap pix(":/images/icons/about_splash.png");
    QSplashScreen splash(pix);
    splash.show();

    QTime dieTime= QTime::currentTime().addSecs(3);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    splash.hide();
    a.start();

    return a.exec();
}

#include <angadiapp.h>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    AngadiApp a(argc, argv);

//    QString app_path;
//    app_path = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
//    QSettings settings(app_path,QSettings::IniFormat);
//    QString language = settings.value("s_language","").toString();

//    QTranslator translator;
//    if(language == "tamil"){
//        translator.load("tamilLanguage_la");
//        a.installTranslator(&translator);
//    }

    /*QPixmap pix(":/images/icons/about_splash.png");
    QSplashScreen splash(pix);
    splash.show();

    QTime dieTime= QTime::currentTime().addSecs(3);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents,50);

    splash.hide();*/
    a.start();

    return a.exec();
}

#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T12:34:31
#
#-------------------------------------------------

QT       += core gui sql xml script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = angadicpp
TEMPLATE = app

DESTDIR = $$PWD

SOURCES += main.cpp\
        login.cpp \
    angadiapp.cpp \
    angadimainwindow.cpp \
    customerform.cpp \
    categoryform.cpp \
    connection.cpp \
    productform.cpp \
    lssbar.cpp \
    models/categoriesmodel.cpp \
    models/productsmodel.cpp \
    models/formvalidation.cpp \
    models/customersmodel.cpp \
    billform.cpp \
    models/billmodel.cpp \
    models/billitemmodel.cpp \
    models/transactionmodel.cpp \
    qtrpt.cpp \
    transactionform.cpp \
    settings.cpp \
    billsettings.cpp \
    timeeditdelegate.cpp \
    rightaligndelegate.cpp \
    unpaidbillreport.cpp
    qtrpt.cpp

HEADERS  += \
    angadiapp.h \
    angadimainwindow.h \
    logindialog.h \
    customerform.h \
    categoryform.h \
    connection.h \
    productform.h \
    lssbar.h \
    models/categoriesmodel.h \
    models/productsmodel.h \
    models/formvalidation.h \
    models/customersmodel.h \
    billform.h \
    models/billmodel.h \
    models/billitemmodel.h \
    models/transactionmodel.h \
    qtrpt.h \
    transactionform.h \
    settings.h \
    billsettings.h \
    timeeditdelegate.h \
    rightaligndelegate.h \
    unpaidbillreport.h \
    qtrpt.h

FORMS    += \
    angadimainwindow.ui \
    logindialog.ui \
    customerform.ui \
    categoryform.ui \
    productform.ui \
    billform.ui \
    transactionform.ui \
    settings.ui \
    billsettings.ui \
    unpaidbillreport.ui

RESOURCES += \
    resource.qrc

TRANSLATIONS += \
            tamilLanguage_la.ts \
            englishLanguage_la.ts

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

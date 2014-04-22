#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T12:34:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = angadicpp
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    angadiapp.cpp \
    angadimainwindow.cpp \
    models/category.cpp \
    customerform.cpp \
    models/customer.cpp \
    categoryform.cpp \
    connection.cpp \
    productform.cpp \
    lssbar.cpp \
    models/product.cpp \
    models/categoriesmodel.cpp \
    models/productsmodel.cpp
HEADERS  += \
    angadiapp.h \
    angadimainwindow.h \
    logindialog.h \
    models/category.h \
    customerform.h \
    models/customer.h \
    categoryform.h \
    connection.h \
    productform.h \
    lssbar.h \
    models/product.h \
    models/categoriesmodel.h \
    models/productsmodel.h

FORMS    += \
    angadimainwindow.ui \
    logindialog.ui \
    customerform.ui \
    categoryform.ui \
    productform.ui

RESOURCES +=

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

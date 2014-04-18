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
    models/customer.cpp
    catagoryform.cpp

HEADERS  += \
    angadiapp.h \
    angadimainwindow.h \
    logindialog.h \
    models/category.h \
    customerform.h \
    models/customer.h
    catagoryform.h

FORMS    += \
    angadimainwindow.ui \
    logindialog.ui \
    customerform.ui
    catagoryform.ui

RESOURCES +=

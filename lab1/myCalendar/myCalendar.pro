#-------------------------------------------------
#
# Project created by QtCreator 2016-08-01T10:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myCalendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calendar.cpp \
    draglabel.cpp

HEADERS  += mainwindow.h \
    calendar.h \
    draglabel.h

FORMS    += mainwindow.ui

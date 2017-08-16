QT += core
QT -= gui

CONFIG += c++11

TARGET = MergeSort
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mythread.cpp \
    mythread2.cpp

HEADERS += \
    mythread.h \
    mythread2.h

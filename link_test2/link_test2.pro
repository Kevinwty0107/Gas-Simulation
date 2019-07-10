#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T23:49:29
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = link_test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Ball.cpp \
    Gas.cpp \
    Plank.cpp \
    proglwidget.cpp \
    stdafx.cpp \
    Vect.cpp \
    Wall.cpp \
    inidialog.cpp

HEADERS  += mainwindow.h \
    Ball.h \
    Gas.h \
    LCG.h \
    Plank.h \
    proglwidget.h \
    stdafx.h \
    Vect.h \
    Wall.h \
    inidialog.h

FORMS    += mainwindow.ui \
    inidialog.ui

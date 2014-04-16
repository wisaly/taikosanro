#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T09:58:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = taikosanro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    determinerange.cpp \
    pixmapmanager.cpp \
    measure.cpp

HEADERS  += mainwindow.h \
    note.h \
    determinerange.h \
    pixmapmanager.h \
    stable.h \
    measure.h

FORMS    += mainwindow.ui

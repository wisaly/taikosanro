#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T09:58:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = taikosanro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    determinerange.cpp \
    pixmapmanager.cpp \
    measure.cpp \
    notecanvas.cpp \
    notechart.cpp \
    notefileparser.cpp \
    song.cpp \
    noteyellowbar.cpp \
    noteballon.cpp

HEADERS  += mainwindow.h \
    note.h \
    determinerange.h \
    pixmapmanager.h \
    stable.h \
    measure.h \
    notecanvas.h \
    notechart.h \
    notefileparser.h \
    song.h \
    noteyellowbar.h \
    noteballon.h

FORMS    += mainwindow.ui

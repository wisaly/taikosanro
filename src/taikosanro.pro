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
    noteballon.cpp \
    determineresult.cpp \
    taikoitem.cpp \
    scoreboard.cpp \
    soulgauge.cpp \
    mainview/taikoitem.cpp \
    mainview/determineresult.cpp \
    mainview/measure.cpp \
    mainview/note.cpp \
    mainview/noteballon.cpp \
    mainview/notecanvas.cpp \
    mainview/notechart.cpp \
    mainview/noteyellowbar.cpp \
    mainview/scoreboard.cpp \
    mainview/soulgauge.cpp

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
    noteballon.h \
    determineresult.h \
    scoreboard.h \
    soulgauge.h \
    mainview/taikoitem.h \
    mainview/determineresult.h \
    mainview/measure.h \
    mainview/note.h \
    mainview/noteballon.h \
    mainview/notecanvas.h \
    mainview/notechart.h \
    mainview/noteyellowbar.h \
    mainview/scoreboard.h \
    mainview/soulgauge.h

FORMS    += mainwindow.ui

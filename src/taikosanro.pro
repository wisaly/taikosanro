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
    pixmapmanager.cpp \
    notefileparser.cpp \
    song.cpp \
    catagory.cpp \
    mainview/determinerange.cpp \
    mainview/mainwindow.cpp \
    mainview/taikoitem.cpp \
    mainview/determineresult.cpp \
    mainview/measure.cpp \
    mainview/note.cpp \
    mainview/noteballon.cpp \
    mainview/notecanvas.cpp \
    mainview/notechart.cpp \
    mainview/noteyellowbar.cpp \
    mainview/scoreboard.cpp \
    mainview/soulgauge.cpp \
    selectview/selectwindow.cpp \
    selectview/selectcanvas.cpp \
    selectview/selectitem.cpp \
    selectview/dirloader.cpp \
    selectview/courseitem.cpp

HEADERS  += stable.h\
    pixmapmanager.h \
    notefileparser.h \
    song.h \
    catagory.h \
    mainview/determinerange.h \
    mainview/mainwindow.h \
    mainview/taikoitem.h \
    mainview/determineresult.h \
    mainview/measure.h \
    mainview/note.h \
    mainview/noteballon.h \
    mainview/notecanvas.h \
    mainview/notechart.h \
    mainview/noteyellowbar.h \
    mainview/scoreboard.h \
    mainview/soulgauge.h \
    selectview/selectwindow.h \
    selectview/selectcanvas.h \
    selectview/selectitem.h \
    selectview/dirloader.h \
    selectview/courseitem.h

FORMS    += selectview/selectwindow.ui \
    mainview/mainwindow.ui

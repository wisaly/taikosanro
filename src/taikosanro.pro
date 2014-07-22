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
    pixmapres.cpp \
    controller.cpp \
    keycontroller.cpp \
    pixmapnumber.cpp \
    mainview/determinerange.cpp \
    mainview/mainwindow.cpp \
    mainview/taikoitem.cpp \
    mainview/determineresult.cpp \
    mainview/measure.cpp \
    mainview/note.cpp \
    mainview/notecanvas.cpp \
    mainview/notechart.cpp \
    mainview/noteyellowbar.cpp \
    mainview/scoreboard.cpp \
    mainview/soulgauge.cpp \
    mainview/score.cpp \
    mainview/hitlight.cpp \
    selectview/selectwindow.cpp \
    selectview/selectcanvas.cpp \
    selectview/selectitem.cpp \
    selectview/dirloader.cpp \
    selectview/courseitem.cpp \
    selectview/selectarrow.cpp \
    mainview/comboitem.cpp \
    mainview/combobubble.cpp \
    mainview/hitbubble.cpp \
    mainview/noteballoon.cpp \
    object.cpp \
    objectscene.cpp

HEADERS  += stable.h\
    pixmapmanager.h \
    notefileparser.h \
    song.h \
    catagory.h \
    pixmapres.h \
    controller.h \
    keycontroller.h \
    pixmapnumber.h \
    mainview/determinerange.h \
    mainview/mainwindow.h \
    mainview/taikoitem.h \
    mainview/determineresult.h \
    mainview/measure.h \
    mainview/note.h \
    mainview/notecanvas.h \
    mainview/notechart.h \
    mainview/noteyellowbar.h \
    mainview/scoreboard.h \
    mainview/soulgauge.h \
    mainview/score.h \
    mainview/hitlight.h \
    selectview/selectwindow.h \
    selectview/selectcanvas.h \
    selectview/selectitem.h \
    selectview/dirloader.h \
    selectview/courseitem.h \
    selectview/selectarrow.h \
    mainview/comboitem.h \
    mainview/combobubble.h \
    mainview/hitbubble.h \
    mainview/noteballoon.h \
    object.h \
    objectscene.h

FORMS    += selectview/selectwindow.ui \
    mainview/mainwindow.ui

OTHER_FILES += \
    ../res/res.ini

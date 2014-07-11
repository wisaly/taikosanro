#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QApplication>
#include <QTextCodec>
#include "mainview/mainwindow.h"
#include "selectview/selectwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    //MainWindow w;
    SelectWindow w;
    w.show();

    return a.exec();
}

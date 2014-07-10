#include <QApplication>
#include "mainview/mainwindow.h"
#include "selectview/selectwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    SelectWindow w;
    w.show();

    return a.exec();
}

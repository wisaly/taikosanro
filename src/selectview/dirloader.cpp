#include "dirloader.h"
#include <QDebug>

DirLoader::DirLoader(QString initPath)
    :dir_(initPath)
{
}

void DirLoader::load()
{
    QStringList entries = dir_.entryList(QDir::Dirs,QDir::Name | QDir::IgnoreCase);
    foreach (QString s, entries) {
        qDebug() << s;
    }
}

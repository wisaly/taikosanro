#ifndef DIRLOADER_H
#define DIRLOADER_H

#include <QDir>
#include <QMap>
#include "../catagory.h"

class DirLoader
{
public:
    DirLoader(QString initPath);

    QList<Catagory> load();

private:
    QDir dir_;
};

#endif // DIRLOADER_H

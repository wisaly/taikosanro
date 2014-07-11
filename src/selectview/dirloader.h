#ifndef DIRLOADER_H
#define DIRLOADER_H

#include <QDir>
#include <QMap>

class DirLoader
{
public:
    DirLoader(QString initPath);

    void load();

private:
    QDir dir_;
};

#endif // DIRLOADER_H

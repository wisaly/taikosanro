#ifndef PIXMAPMANAGER_H
#define PIXMAPMANAGER_H

#include <QPixmap>

class PixmapManager
{
    PixmapManager();
public:
    static QPixmap get(QString path);

    static bool loadAll();
};

#endif // PIXMAPMANAGER_H

#ifndef PIXMAPMANAGER_H
#define PIXMAPMANAGER_H

#include <QPixmap>

class PixmapManager
{
    PixmapManager();
public:
    static QPixmap get(QString path);

    static QPixmap getRedMarker();
    static QPixmap getBlueMarker();
    static QPixmap getBigRedMarker();
    static QPixmap getBigBlueMarker();

    static bool loadAll();
};

#endif // PIXMAPMANAGER_H

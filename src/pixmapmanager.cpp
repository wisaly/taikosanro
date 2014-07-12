#include "pixmapmanager.h"
#include <QHash>

typedef QHash<QString,QPixmap> PixmapHash;

Q_GLOBAL_STATIC(PixmapHash,pixmapHash)

QPixmap PixmapManager::get(QString path)
{
    if(!pixmapHash->contains(path))
    {
        QPixmap pixmap;
        if(!pixmap.load(path))
        {
            return QPixmap();
        }

        pixmapHash->insert(
                    path,
                    pixmap);
    }

    return (*pixmapHash)[path];
}

bool PixmapManager::loadAll()
{

    return true;
}

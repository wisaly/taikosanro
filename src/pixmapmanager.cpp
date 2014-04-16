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

QPixmap PixmapManager::getRedMarker()
{
    return get("../res/redmarker.png");
}

QPixmap PixmapManager::getBlueMarker()
{
    return get("../res/bluemarker.png");
}

QPixmap PixmapManager::getBigRedMarker()
{
    return get("../res/bigredmarker.png");
}

QPixmap PixmapManager::getBigBlueMarker()
{
    return get("../res/bigbluemarker.png");
}

bool PixmapManager::loadAll()
{
    if(getRedMarker().isNull())
    {
        return false;
    }
    if(getBlueMarker().isNull())
    {
        return false;
    }
    if(getBigRedMarker().isNull())
    {
        return false;
    }
    if(getBigBlueMarker().isNull())
    {
        return false;
    }

    return true;
}

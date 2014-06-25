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

QPixmap PixmapManager::getYellowBarBody()
{
    return get("../res/yellowbarbody.png");
}

QPixmap PixmapManager::getYellowBarHead()
{
    return get("../res/yellowbarhead.png");
}

QPixmap PixmapManager::getYellowBarTail()
{
    return get("../res/yellowbartail.png");
}

QPixmap PixmapManager::getBigYellowBarBody()
{
    return get("../res/bigyellowbarbody.png");
}

QPixmap PixmapManager::getBigYellowBarHead()
{
    return get("../res/bigyellowbarhead.png");
}

QPixmap PixmapManager::getBigYellowBarTail()
{
    return get("../res/bigyellowbartail.png");
}

bool PixmapManager::loadAll()
{
    if (getRedMarker().isNull())
        return false;
    if (getBlueMarker().isNull())
        return false;
    if (getBigRedMarker().isNull())
        return false;
    if (getBigBlueMarker().isNull())
        return false;
    if (getYellowBarBody().isNull())
        return false;
    if (getYellowBarHead().isNull())
        return false;
    if (getYellowBarTail().isNull())
        return false;
    if (getBigYellowBarBody().isNull())
        return false;
    if (getBigYellowBarHead().isNull())
        return false;
    if (getBigYellowBarTail().isNull())
        return false;

    return true;
}

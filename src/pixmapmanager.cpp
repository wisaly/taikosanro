#include <QHash>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include "pixmapmanager.h"
#include "stable.h"

typedef QHash<QString,PixmapRes> PixmapResHash;

Q_GLOBAL_STATIC(PixmapResHash,pixmapHash)
Q_GLOBAL_STATIC_WITH_ARGS(QSettings,resSetting,(Ts::RES_FILE,QSettings::IniFormat))
Q_GLOBAL_STATIC_WITH_ARGS(QDir,resDir,(QFileInfo(Ts::RES_FILE).dir()))

PixmapRes PixmapManager::get(QString key)
{
    if (!resSetting->contains(key))
    {
        qDebug() << "PixmapManager::get invalid key :" << key;
        return PixmapRes();
    }

    QString path = resDir->filePath(resSetting->value(key).toString());
    if (!pixmapHash->contains(path))
    {
        PixmapRes pixmap;
        if (!pixmap.load(path))
        {
            return PixmapRes();
        }

        // load position
        pixmap.setPos(getPos(key + "/pos"));

        // load extend
        pixmap.setExtend(getSize(key + "/extend"));

        pixmapHash->insert(
                    key,
                    pixmap);
    }

    return (*pixmapHash)[key];
}

QPointF PixmapManager::getPos(QString key)
{
    if (resSetting->contains(key))
    {
        QStringList val = resSetting->value(key).toStringList();
        if (val.count() == 2)
        {
            return QPointF(val[0].toDouble(),val[1].toDouble());
        }
    }

    return QPointF();
}

QSizeF PixmapManager::getSize(QString key)
{
    if (resSetting->contains(key))
    {
        QStringList val = resSetting->value(key).toStringList();
        if (val.count() == 2)
        {
            return QSizeF(val[0].toDouble(),val[1].toDouble());
        }
    }

    return QSizeF();
}

bool PixmapManager::loadAll()
{

    return true;
}

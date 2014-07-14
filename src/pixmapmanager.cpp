#include <QHash>
#include <QSettings>
#include <QDir>
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
        QString posKey = key + "/pos";
        if (resSetting->contains(posKey))
        {
            QStringList posVal = resSetting->value(posKey).toString().split(',',QString::SkipEmptyParts);
            if (posVal.count() == 2)
            {
                pixmap.setPos(QPointF(posVal[0].toDouble(),posVal[1].toDouble()));
            }
        }
        // load strenth
        QString strenthKey = key + "/strenth";
        if (resSetting->contains(strenthKey))
        {
            QStringList strenthVal = resSetting->value(strenthKey).toString().split(',',QString::SkipEmptyParts);
            if (strenthVal.count() == 2)
            {
                pixmap.setStrenth(QSizeF(strenthVal[0].toDouble(),strenthVal[1].toDouble()));
            }
        }

        pixmapHash->insert(
                    key,
                    pixmap);
    }

    return (*pixmapHash)[key];
}

bool PixmapManager::loadAll()
{

    return true;
}

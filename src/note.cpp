#include "note.h"
#include "pixmapmanager.h"
#include "stable.h"

#include <QPainter>

Note::Note(Type noteType, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    switch (noteType) {
    case RedMarker:
        notePixmap = PixmapManager::getRedMarker();
        break;
    case BlueMarker:
        notePixmap = PixmapManager::getBlueMarker();
        break;
    case BigRedMarker:
        notePixmap = PixmapManager::getBigRedMarker();
        break;
    case BigBlueMarker:
        notePixmap = PixmapManager::getBigBlueMarker();
        break;
    default:
        Q_ASSERT(false);
        break;
    }

    this->noteType = noteType;
}

QRectF Note::boundingRect() const
{
    return notePixmap.rect();
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(this->pos(),notePixmap);
}

void Note::advance(int step)
{
    Q_UNUSED(step);
}

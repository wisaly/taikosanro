#include "note.h"
#include "pixmapmanager.h"
#include "stable.h"

#include <QPainter>

Note::Note(Type noteType, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    switch (noteType) {
    case RedMarker:
        notePixmap_ = PixmapManager::getRedMarker();
        break;
    case BlueMarker:
        notePixmap_ = PixmapManager::getBlueMarker();
        break;
    case BigRedMarker:
        notePixmap_ = PixmapManager::getBigRedMarker();
        break;
    case BigBlueMarker:
        notePixmap_ = PixmapManager::getBigBlueMarker();
        break;
    default:
        Q_ASSERT(true);
        break;
    }

    this->noteType_ = noteType;
}

QRectF Note::boundingRect() const
{
    return notePixmap_.rect();
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(notePixmap_.rect(),notePixmap_);
}

void Note::advance(int step)
{
    Q_UNUSED(step);
}

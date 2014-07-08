#include "note.h"
#include "pixmapmanager.h"
#include "stable.h"

#include <QPainter>

Note::Note(QGraphicsItem *parent, Type noteType, int index)
    :QGraphicsItem(parent),index_(index)
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
        break;
    }

    noteType_ = noteType;

    setCacheMode(DeviceCoordinateCache);
}

QRectF Note::boundingRect() const
{
    return notePixmap_.rect();
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //QRect dstRect = notePixmap_.rect();

    painter->drawPixmap(0,0,Ts::NOTE_WIDTH,Ts::NOTE_HEIGHT,notePixmap_);
}

int Note::index()
{
    return index_;
}

void Note::setDetermineTime(int elapsed)
{
    determineRange_.setRange(elapsed);
}

Ts::DetermineValue Note::determine(int elapsed)
{
    return determineRange_.determine(elapsed);
}

bool Note::acceptAct(Ts::TaikoState action)
{
    if ((action & Ts::DON_BOTH &&
            (noteType_ == RedMarker || noteType_ == BigRedMarker)) ||
        (action & Ts::KA_BOTH &&
            (noteType_ == BlueMarker || noteType_ == BigBlueMarker)))
        return true;

    return false;
}

void Note::setUnitWidth(int unitWidth)
{
    unitWidth_ = unitWidth;
}

void Note::advance(int step)
{
    Q_UNUSED(step);
}

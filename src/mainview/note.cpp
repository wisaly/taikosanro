#include "note.h"
#include "../pixmapmanager.h"
#include "../stable.h"

#include <QPainter>

Note::Note(QGraphicsItem *parent, Type noteType, int index)
    :QGraphicsObject(parent),index_(index)
{
    switch (noteType) {
    case RedMarker:
        notePixmap_ = PixmapManager::get(Ts::mv::RED_MARKER);
        break;
    case BlueMarker:
        notePixmap_ = PixmapManager::get(Ts::mv::BLUE_MARKER);
        break;
    case BigRedMarker:
        notePixmap_ = PixmapManager::get(Ts::mv::BIG_RED_MARKER);
        break;
    case BigBlueMarker:
        notePixmap_ = PixmapManager::get(Ts::mv::BIG_BLUE_MARKER);
        break;
    default:
        break;
    }

    noteType_ = noteType;

    setCacheMode(DeviceCoordinateCache);

    rect_ = QRectF(0,0,
                   notePixmap_.width() + notePixmap_.pos().x(),
                   notePixmap_.height() + notePixmap_.pos().y());
}

QRectF Note::boundingRect() const
{
    return rect_;
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //QRect dstRect = notePixmap_.rect();

    painter->drawPixmap(notePixmap_.pos(),notePixmap_);
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

void Note::moveOut(Ts::DetermineValue value)
{
    Q_UNUSED(value)
    hide();
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

void Note::advance(int phase)
{
    Q_UNUSED(phase);
}

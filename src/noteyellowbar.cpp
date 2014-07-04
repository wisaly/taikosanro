#include "noteyellowbar.h"
#include "pixmapmanager.h"
#include "stable.h"

#include <QPainter>

NoteYellowBar::NoteYellowBar(QGraphicsItem *parent, int index, bool isBig, int length)
    :Note(parent,isBig ? Note::BigYellowBar : Note::YellowBar,index),
      length_(length),hitCount_(0)
{
    if (isBig)
    {
        notePixmap_ = PixmapManager::getBigYellowBarBody();
        noteHeadPixmap_ = PixmapManager::getBigYellowBarHead();
        noteTailPixmap_ = PixmapManager::getBigYellowBarTail();
    }
    else
    {
        notePixmap_ = PixmapManager::getYellowBarBody();
        noteHeadPixmap_ = PixmapManager::getYellowBarHead();
        noteTailPixmap_ = PixmapManager::getYellowBarTail();
    }
}

void NoteYellowBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF headRect(0,0,Ts::NOTE_WIDTH,Ts::NOTE_HEIGHT);
    QRectF tailRect(0,0,Ts::NOTE_WIDTH,Ts::NOTE_HEIGHT);
    QRectF bodyRect(0,0,Ts::NOTE_WIDTH,Ts::NOTE_HEIGHT);
    tailRect.moveLeft(length_ * unitWidth_ - tailRect.width());
    bodyRect.setLeft(headRect.width() / 2);
    bodyRect.setRight(length_ * unitWidth_ - tailRect.width() / 2);

    painter->drawPixmap(headRect,noteHeadPixmap_,noteHeadPixmap_.rect());
    painter->drawPixmap(tailRect,noteTailPixmap_,noteTailPixmap_.rect());
    painter->drawPixmap(bodyRect,notePixmap_,notePixmap_.rect());
}

int NoteYellowBar::length() const
{
    return length_;
}

int NoteYellowBar::hitCount() const
{
    return hitCount_;
}

void NoteYellowBar::setHitCount(int hitCount)
{
    hitCount_ = hitCount;
}




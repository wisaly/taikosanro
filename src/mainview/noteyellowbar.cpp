#include "noteyellowbar.h"
#include "../pixmapmanager.h"
#include "../stable.h"

#include <QPainter>

NoteYellowBar::NoteYellowBar(QGraphicsItem *parent, int index, bool isBig)
    :Note(parent,isBig ? Note::BigYellowBar : Note::YellowBar,index),
      length_(1),
      hitCount_(0)
{
    if (isBig)
    {
        notePixmap_ = PixmapManager::get(Ts::mv::BIG_YELLOW_BAR_BODY);
        headPixmap_ = PixmapManager::get(Ts::mv::BIG_YELLOW_BAR_HEAD);
        tailPixmap_ = PixmapManager::get(Ts::mv::BIG_YELLOW_BAR_TAIL);
    }
    else
    {
        notePixmap_ = PixmapManager::get(Ts::mv::YELLOW_BAR_BODY);
        headPixmap_ = PixmapManager::get(Ts::mv::YELLOW_BAR_HEAD);
        tailPixmap_ = PixmapManager::get(Ts::mv::YELLOW_BAR_TAIL);
    }
}

void NoteYellowBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF headRect(headPixmap_.pos(),headPixmap_.size());
    QRectF tailRect(headPixmap_.pos(),tailPixmap_.size());
    QRectF bodyRect(headPixmap_.pos(),notePixmap_.size());
    tailRect.moveLeft(length_ * unitWidth_ - tailRect.width() - headRect.left());
    bodyRect.setLeft(headRect.width());
    bodyRect.setRight(tailRect.left());

    painter->drawPixmap(tailRect,tailPixmap_,tailPixmap_.rect());
    painter->drawPixmap(bodyRect,notePixmap_,notePixmap_.rect());
    painter->drawPixmap(headRect,headPixmap_,headPixmap_.rect());
}

Ts::DetermineValue NoteYellowBar::determine(int elapsed)
{
    if (elapsed < determineRange_.appearElapsed())
    {
        return Ts::OUTSIDE;
    }
    if (elapsed > (determineRange_.appearElapsed() + timeLength_))
    {
        return Ts::PASS;
    }

    return Ts::CONSECUTIVE_HIT;
}

bool NoteYellowBar::acceptAct(Ts::TaikoState action)
{
    return (action & Ts::DON_BOTH) || (action & Ts::KA_BOTH);
}

void NoteYellowBar::setUnitWidth(int unitWidth)
{
    Note::setUnitWidth(unitWidth);

    rect_ = QRectF(0,0,length_ * unitWidth_,Ts::NOTE_HEIGHT);
}




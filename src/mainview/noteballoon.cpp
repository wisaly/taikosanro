#include <QPainter>
#include <QDebug>
#include "noteballoon.h"

NoteBalloon::NoteBalloon(QGraphicsItem *parent, int index) :
    Note(parent,Note::Balloon,index),
      count_(0),
      hitCount_(0)
{
}

void NoteBalloon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(0,0,length_ * unitWidth_,100,Qt::white);
}

bool NoteBalloon::acceptAct(Ts::TaikoState action)
{
    return action & Ts::DON_BOTH;
}

Ts::DetermineValue NoteBalloon::determine(int elapsed)
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

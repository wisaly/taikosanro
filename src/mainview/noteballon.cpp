#include <QPainter>
#include <QDebug>
#include "noteballon.h"

NoteBallon::NoteBallon(QGraphicsItem *parent, int index) :
    Note(parent,Note::Ballon,index),
      count_(0),
      hitCount_(0)
{
}

void NoteBallon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(0,0,length_ * unitWidth_,Ts::NOTE_HEIGHT,Qt::white);
}

bool NoteBallon::acceptAct(Ts::TaikoState action)
{
    return action & Ts::DON_BOTH;
}

Ts::DetermineValue NoteBallon::determine(int elapsed)
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

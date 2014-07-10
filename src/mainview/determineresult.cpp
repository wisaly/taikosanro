#include "determineresult.h"
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QSignalTransition>

DetermineResult::DetermineResult(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
}

QRectF DetermineResult::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void DetermineResult::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(QFont("华文行楷",15));
    switch (result_)
    {
    case Ts::OUTSIDE:
        break;
    case Ts::GREAT:
        painter->drawText(boundingRect(),Qt::AlignCenter,"良");
        break;
    case Ts::GOOD:
        painter->drawText(boundingRect(),Qt::AlignCenter,"可");
        break;
    case Ts::FAIL:
        painter->drawText(boundingRect(),Qt::AlignCenter,"不可");
        break;
    case Ts::MISS:
        painter->drawText(boundingRect(),Qt::AlignCenter,"Miss");
        break;
    }
}

void DetermineResult::advance(int step)
{
    if (step)
    {

    }
}

void DetermineResult::determined(Ts::DetermineValue value)
{
    if (value == Ts::OUTSIDE)
        return;

    result_ = value;

    QPropertyAnimation *aniPos = new QPropertyAnimation(this,"y");
    aniPos->setKeyValueAt(0,0);
    aniPos->setKeyValueAt(0.6,-30);
    aniPos->setKeyValueAt(1,-30);
    aniPos->setDuration(300);
    QPropertyAnimation *aniVisable = new QPropertyAnimation(this,"opacity");
    aniVisable->setKeyValueAt(0,0);
    aniVisable->setKeyValueAt(0.3,1);
    aniVisable->setKeyValueAt(0.6,1);
    aniVisable->setKeyValueAt(1,0);
    aniVisable->setDuration(300);

    QParallelAnimationGroup *animation = new QParallelAnimationGroup();
    animation->addAnimation(aniPos);
    animation->addAnimation(aniVisable);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


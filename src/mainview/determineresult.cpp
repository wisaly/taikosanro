#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QSignalTransition>
#include "determineresult.h"
#include "../pixmapmanager.h"

DetermineResult::DetermineResult(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    rect_ = QRectF(QPointF(0,0),PixmapManager::getSize(Ts::mv::DETRESULT_SIZE));
    pos1_ = PixmapManager::getPos(Ts::mv::DETRESULT_POS1);
    pos2_ = PixmapManager::getPos(Ts::mv::DETRESULT_POS2);

    greatPixmap_ = PixmapManager::get(Ts::mv::DETGREAT);
    goodPixmap_ = PixmapManager::get(Ts::mv::DETGOOD);
    failPixmap_ = PixmapManager::get(Ts::mv::DETFAIL);
}

void DetermineResult::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(QFont(Ts::GUI_FONT_NAME,15));
    switch (result_)
    {
    case Ts::GREAT:
        painter->drawPixmap(greatPixmap_.pos(),greatPixmap_);
        break;
    case Ts::GOOD:
        painter->drawPixmap(goodPixmap_.pos(),goodPixmap_);
        break;
    case Ts::FAIL:
        painter->drawPixmap(failPixmap_.pos(),failPixmap_);
        break;
    default:
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

    QPropertyAnimation *aniPos = new QPropertyAnimation(this,"pos");
    aniPos->setKeyValueAt(0,pos1_);
    aniPos->setKeyValueAt(0.6,pos2_);
    aniPos->setKeyValueAt(1,pos2_);
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


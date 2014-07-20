#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include "hitbubble.h"
#include "../pixmapmanager.h"
#include "../stable.h"

HitBubble::HitBubble(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    hide();

    backPixmap_ = PixmapManager::get(Ts::mv::HIT_BUBBLE);
    textPixmap_ = PixmapManager::get(Ts::mv::HITBUBTEXT);

    numberRect_ = QRectF(PixmapManager::getPos(Ts::mv::HITBUBNUM_OFFSET),
                         PixmapManager::getSize(Ts::mv::HITBUBNUM_SIZE));
    numberScaleRect_ = numberRect_.adjusted(0,numberRect_.height() / 5,0,0);
    number_ = new PixmapNumber(this);
    number_->setAlign(Qt::AlignRight);
    number_->addPixmapGroup(Ts::mv::SCORE);
    number_->setRect(numberRect_);
}

void HitBubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,backPixmap_);
    painter->drawPixmap(textPixmap_.pos(),textPixmap_);
}

void HitBubble::consecutiveChanged(int count)
{
    if (count == 0)
        return;

    number_->setNumber(count);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    QPropertyAnimation *animation = new QPropertyAnimation(this,"opacity");
    animation->setDuration(3000);
    animation->setKeyValueAt(0.00,1);
    animation->setKeyValueAt(0.97,1);
    animation->setKeyValueAt(1.00,0);
    group->addAnimation(animation);

    QPropertyAnimation *numberAnimation = new QPropertyAnimation(number_,"rect");
    numberAnimation->setDuration(300);
    numberAnimation->setKeyValueAt(0.0,numberRect_);
    numberAnimation->setKeyValueAt(0.5,numberScaleRect_);
    numberAnimation->setKeyValueAt(1.0,numberRect_);
    group->addAnimation(numberAnimation);

    this->connect(group,SIGNAL(finished()),SLOT(animationFinished()));
    show();
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void HitBubble::animationFinished()
{
    hide();
}

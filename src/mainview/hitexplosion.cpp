#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "hitexplosion.h"
#include "../pixmapmanager.h"

HitExplosion::HitExplosion(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    rect_.setSize(PixmapManager::getSize(Ts::mv::EXPLOSION_SIZE));

    basePixmap_ = PixmapManager::get(Ts::mv::EXPLOSION_BASE);

    PixmapRes greatPixmap = PixmapManager::get(Ts::mv::EXPLOSION_GREAT);
    greatItem_ = new QGraphicsPixmapItem(greatPixmap,this);
    greatItem_->setPos(greatPixmap.pos());
    greatItem_->hide();

    PixmapRes goodPixmap = PixmapManager::get(Ts::mv::EXPLOSION_GOOD);
    goodItem_ = new QGraphicsPixmapItem(goodPixmap,this);
    goodItem_->setPos(goodPixmap.pos());
    goodItem_->hide();

    hide();
}

void HitExplosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(basePixmap_.pos(),basePixmap_);
}

QRectF HitExplosion::boundingRect() const
{
    return rect_;
}

void HitExplosion::determined(Ts::DetermineValue value)
{
    if (value == Ts::GOOD)
    {
        greatItem_->hide();
        goodItem_->show();
    }
    else if (value == Ts::GREAT)
    {
        goodItem_->hide();
        greatItem_->show();
    }
    else
    {
        return;
    }

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    QPropertyAnimation *animation = new QPropertyAnimation(this,"opacity");
    animation->setDuration(200);
    animation->setKeyValueAt(0.0,0.0);
    animation->setKeyValueAt(0.1,0.5);
    animation->setKeyValueAt(0.9,0.5);
    animation->setKeyValueAt(1.0,0.0);
    group->addAnimation(animation);

    show();
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

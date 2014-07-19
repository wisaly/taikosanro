#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>
#include "combobubble.h"
#include "../pixmapmanager.h"
#include "../stable.h"

ComboBubble::ComboBubble(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    hide();

    backItem_ = new QGraphicsPixmapItem(PixmapManager::get(Ts::mv::COMBO_BUBBLE),this);
    backItem_->setTransformOriginPoint(backItem_->boundingRect().center());
    backItem_->setTransformationMode(Qt::SmoothTransformation);

    breakItem_ = new QGraphicsPixmapItem(PixmapManager::get(Ts::mv::COMBO_BREAK),this);

    number_ = new PixmapNumber(this);
    number_->setAlign(Qt::AlignRight);
    number_->addPixmapGroup(Ts::mv::HIT);
    number_->setRect(QRectF(QPointF(0,0),
                            PixmapManager::getSize(Ts::mv::COMBOBUBNUM_SIZE)));
    number_->setPos(PixmapManager::getPos(Ts::mv::COMBOBUBNUM_OFFSET));
}

void ComboBubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void ComboBubble::comboChanged(int combo)
{
    if (!(combo % 10 == 0))
        return;

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    QPropertyAnimation *animation = new QPropertyAnimation(this,"opacity");
    animation->setDuration(1000);
    animation->setKeyValueAt(0.0,0);
    animation->setKeyValueAt(0.2,1);
    animation->setKeyValueAt(0.8,1);
    animation->setKeyValueAt(1.0,0);
    group->addAnimation(animation);

    this->connect(group,SIGNAL(finished()),SLOT(animationFinished()));

    if (combo == 0)
    {
        backItem_->hide();
        number_->hide();

        breakItem_->show();
    }
    else
    {
        breakItem_->hide();

        number_->setNumber(combo);
        number_->show();
        backItem_->show();

        QPropertyAnimation *scaleAnimation = new QPropertyAnimation(this,"backScale");
        scaleAnimation->setDuration(1000);
        scaleAnimation->setKeyValueAt(0.0,0.9);
        scaleAnimation->setKeyValueAt(0.1,1.0);
        scaleAnimation->setKeyValueAt(0.3,0.9);
        scaleAnimation->setKeyValueAt(1.0,0.9);

        group->addAnimation(scaleAnimation);
    }

    show();
    group->start(QPropertyAnimation::DeleteWhenStopped);
}

void ComboBubble::animationFinished()
{
    hide();
}

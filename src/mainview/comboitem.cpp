#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include "comboitem.h"
#include "../pixmapmanager.h"
#include "../stable.h"

ComboItem::ComboItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    rect_.setSize(PixmapManager::getSize(Ts::mv::COMBO_SIZE));
    numberRect_.setSize(PixmapManager::getSize(Ts::mv::COMBONUMBER_SIZE));
    numberScaleRect_ = numberRect_;
    numberScaleRect_.setTop(-numberRect_.height() / 5);

    number_ = new PixmapNumber(this);
    number_->hide();
    number_->addPixmapGroup(Ts::mv::COMBO);
    number_->addPixmapGroup(Ts::mv::COMBO_RED);
    number_->setAlign(Qt::AlignCenter);
    number_->setRect(numberRect_);
    number_->setPos(PixmapManager::getPos(Ts::mv::COMBONUMBER_OFFSET));
}

void ComboItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void ComboItem::comboChanged(int combo)
{
    if (combo < 10)
    {
        number_->hide();
        number_->setCurrentGroup(0);
        return;
    }

    number_->show();

    if (combo > 100)
    {
        number_->setCurrentGroup(1);
    }

    number_->setNumber(combo);

    // perform animation
    QPropertyAnimation *animation = new QPropertyAnimation(number_,"rect");
    animation->setDuration(150);
    animation->setKeyValueAt(0.0,numberRect_);
    animation->setKeyValueAt(0.5,numberScaleRect_);
    animation->setKeyValueAt(1.0,numberRect_);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

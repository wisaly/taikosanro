#include "selectcanvas.h"

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDebug>
#include "../stable.h"

SelectCanvas::SelectCanvas(QGraphicsItem *parent) :
    QGraphicsObject(parent),current_(0)
{
}

QRectF SelectCanvas::boundingRect() const
{
    return rect_;
}

void SelectCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

SelectItem *SelectCanvas::addItem()
{
    SelectItem *item = new SelectItem(this);
    items_.append(item);
    //item->setX(50 * (items_.count() - 1));

    return item;
}

void SelectCanvas::move(int step)
{
    // out of range
    if ((current_ == 0 && step < 0) ||
            (current_ == (items_.count() - 1) && step > 0))
        return;

    // out of range but still could move
    if (current_ + step < 0)
    {
        step = current_;
    }
    else if (current_ + step >= items_.count())
    {
        step = items_.count() - 1 - current_;
    }

    items_[current_]->resetBoundingRect();

    QParallelAnimationGroup *groupMove = new QParallelAnimationGroup(this);

    for (int i = 0;i < items_.count();i++)
    {
        int xFrom = (i - current_) * Ts::BAR_WIDTH + rect_.width() / 2;
        int xTo = xFrom - Ts::BAR_WIDTH * step;
        if (step == 0 || xTo - Ts::BAR_WIDTH > rect_.width() || xTo + Ts::BAR_WIDTH < 0)
        {
            items_[i]->setX(xTo);
            continue;
        }
        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        //animation->setStartValue(xFrom);
        items_[i]->setX(xFrom);
        animation->setEndValue(xTo);
        animation->setDuration(300);

        groupMove->addAnimation(animation);
    }


    this->connect(groupMove,SIGNAL(finished()),SLOT(moveFinished()));
    groupMove->start(QAbstractAnimation::DeleteWhenStopped);
    current_ += step;
}

void SelectCanvas::moveFinished()
{
    QParallelAnimationGroup *groupScale = new QParallelAnimationGroup(this);
    QPropertyAnimation *aniScale = new QPropertyAnimation(items_[current_],"boundingRect");
    aniScale->setDuration(300);
    aniScale->setEndValue(QRectF(0 - Ts::BAR_EXPAND / 2,0,Ts::BAR_EXPAND,Ts::BAR_HEIGHT));
    groupScale->addAnimation(aniScale);

    for (int i = current_ + 1;i < items_.count();i++)
    {
        if (items_[i]->x() > rect_.width())
            break;

        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        animation->setDuration(300);
        animation->setEndValue(items_[i]->x() + (Ts::BAR_EXPAND - Ts::BAR_WIDTH) / 2);
        groupScale->addAnimation(animation);
    }

    for (int i = current_ - 1;i >= 0;i--)
    {
        if (items_[i]->x() + Ts::BAR_WIDTH < 0)
            break;

        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        animation->setDuration(300);
        animation->setEndValue(items_[i]->x() - (Ts::BAR_EXPAND - Ts::BAR_WIDTH) / 2);
        groupScale->addAnimation(animation);
    }
    groupScale->start(QAbstractAnimation::DeleteWhenStopped);
}




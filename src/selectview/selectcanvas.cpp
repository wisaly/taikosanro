#include "selectcanvas.h"

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDebug>

SelectCanvas::SelectCanvas(QGraphicsItem *parent) :
    QGraphicsObject(parent),currentItem_(0)
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
    if ((currentItem_ == 0 && step < 0) ||
            (currentItem_ == (items_.count() - 1) && step > 0))
        return;

    // out of range but still could move
    if (currentItem_ + step < 0)
    {
        step = currentItem_;
    }
    else if (currentItem_ + step > items_.count())
    {
        step = items_.count() - 1 - currentItem_;
    }

    //items_[currentItem_]->setBoundingRect(QRect(0,0,50,200));

    QParallelAnimationGroup *groupMove = new QParallelAnimationGroup(this);
    for (int i = 0;i < items_.count();i++)
    {
        int xFrom = (i - currentItem_) * 50 + rect_.width() / 2 - 25;
        int xTo = xFrom - 50 * step;
        if (step == 0 || xTo - 50 > rect_.width() || xTo + 50 < 0)
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

    currentItem_ += step;

//    QParallelAnimationGroup *groupScale = new QParallelAnimationGroup(this);
//    QPropertyAnimation *aniScale = new QPropertyAnimation(items_[currentItem_],"boundingRect");
//    aniScale->setDuration(300);
//    aniScale->setStartValue(QRectF(0,0,50,200));
//    aniScale->setEndValue(QRectF(-50,0,150,200));

//    for (int i = currentItem_;i >= 0;i--)
//    {
//        if (items_[i]->x() + 50 < 0)
//        {
//            break;
//        }

//        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
//        animation->setDuration(300);
//        animation->setEndValue(items_[i]->x() - 100);
//        groupScale->addAnimation(animation);
//    }
//    for (int i = currentItem_;i < items_.count();i++)
//    {
//        if (items_[i]->x() - 50 > rect_.width())
//        {
//            break;
//        }

//        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
//        animation->setDuration(300);
//        animation->setEndValue(items_[i]->x() + 100);
//        groupScale->addAnimation(animation);
//    }

//    groupScale->addAnimation(aniScale);

//    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
//    group->addAnimation(groupMove);
//    group->addAnimation(groupScale);
    groupMove->start(QAbstractAnimation::DeleteWhenStopped);
}




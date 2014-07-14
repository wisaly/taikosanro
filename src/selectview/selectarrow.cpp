#include <QPainter>
#include <QPropertyAnimation>
#include "selectarrow.h"
#include "../pixmapmanager.h"

SelectArrow::SelectArrow(QGraphicsItem *parent)
    :QGraphicsObject(parent),current_(0)
{
    setCacheMode(DeviceCoordinateCache);

    arrowPixmap_ = PixmapManager::get(Ts::sv::SELECT_ARROW);
}

QRectF SelectArrow::boundingRect() const
{
    return arrowPixmap_.rect();
}

void SelectArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,arrowPixmap_);
}

void SelectArrow::addSelection(Ts::Course course, QPointF pos)
{
    selections_.append(QPair<Ts::Course,QPointF>(course,pos));

    if (selections_.count() == 1)
    {
        current_ = 0;
        moveSelection(0);
    }
}

void SelectArrow::moveSelection(int step)
{
    if (selections_.count() == 0)
    {
        return;
    }

    int target = (current_ + step) < 0 ?
                (current_ + step) % selections_.count() + selections_.count() :
                (current_ + step) % selections_.count();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"pos");
    animation->setDuration(300);
    animation->setStartValue(selections_[current_].second);
    animation->setEndValue(selections_[target].second);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    current_ = target;
}

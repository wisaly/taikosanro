#include "selectitem.h"
#include <QPainter>

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),rect_(0,0,50,200)
{
}



void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect().adjusted(5,5,-5,-5);
    painter->drawRect(rect);

    painter->drawText(rect,Qt::AlignCenter,titleVert_);
}

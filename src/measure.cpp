#include "measure.h"

Measure::Measure(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
}

QRectF Measure::boundingRect() const
{
    return canvasRect;
}

void Measure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void Measure::advance(int step)
{

}

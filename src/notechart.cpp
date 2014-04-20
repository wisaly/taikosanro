#include "notechart.h"

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsItem(parent),rect_(0,0,700,100)
{
}

QRectF NoteChart::boundingRect() const
{
    return rect_;
}

void NoteChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void NoteChart::advance(int step)
{
    
}

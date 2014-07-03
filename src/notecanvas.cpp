#include "notecanvas.h"

NoteCanvas::NoteCanvas(QGraphicsItem *parent)
    :QGraphicsItem(parent),rect_(0,0,1000,100)
{
}

QRectF NoteCanvas::boundingRect() const
{
    return rect_;
}

void NoteCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void NoteCanvas::advance(int step)
{
    Q_UNUSED(step);
}

#include "notecanvas.h"

NoteCanvas::NoteCanvas(QGraphicsItem *parent)
    :QGraphicsItem(parent),rect_(0,0,700,100)
{
}

QRectF NoteCanvas::boundingRect() const
{
    return rect_;
}

void NoteCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void NoteCanvas::advance(int step)
{

}

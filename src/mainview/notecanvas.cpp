#include "notecanvas.h"
#include <QPainter>

NoteCanvas::NoteCanvas(QGraphicsItem *parent)
    :QGraphicsItem(parent),rect_(0,0,821,114) // ratio=7.2
{

}

QRectF NoteCanvas::boundingRect() const
{
    return rect_;
}

void NoteCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawEllipse(QPointF(Ts::NOTE_WIDTH / 2,Ts::NOTE_HEIGHT / 2),Ts::NOTE_WIDTH / 3,Ts::NOTE_HEIGHT / 3);
    painter->drawEllipse(QPointF(Ts::NOTE_WIDTH / 2,Ts::NOTE_HEIGHT / 2),Ts::NOTE_WIDTH / 5,Ts::NOTE_HEIGHT / 5);
}

void NoteCanvas::advance(int step)
{
    Q_UNUSED(step);
}

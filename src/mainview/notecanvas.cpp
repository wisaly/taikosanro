#include <QPainter>
#include <QDebug>
#include "notecanvas.h"
#include "../pixmapmanager.h"

NoteCanvas::NoteCanvas(QGraphicsItem *parent) :
    QGraphicsItem(parent),rect_(0,0,821,114) // ratio=7.2
{
    backPixmap_ = PixmapManager::get(Ts::mv::CANVAS_BACK);
    circlePixmap_ = PixmapManager::get(Ts::mv::DETERMINE_CIRCLE);

    rect_ = QRectF(backPixmap_.pos(),backPixmap_.extend());
}

QRectF NoteCanvas::boundingRect() const
{
    return rect_;
}

void NoteCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(rect_,backPixmap_,backPixmap_.rect());
    painter->drawPixmap(circlePixmap_.pos(),circlePixmap_);
}

void NoteCanvas::advance(int step)
{
    Q_UNUSED(step);
}

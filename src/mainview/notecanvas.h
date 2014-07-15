#ifndef NOTECANVAS_H
#define NOTECANVAS_H

#include "measure.h"

#include <QGraphicsItem>

class NoteCanvas : public QGraphicsItem
{
public:
    NoteCanvas(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:
    void advance(int step);

private:
    QRectF rect_;
    QList<Measure*> measures_;
    PixmapRes backPixmap_;
    PixmapRes circlePixmap_;
};

#endif // NOTECANVAS_H

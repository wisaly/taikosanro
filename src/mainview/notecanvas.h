#ifndef NOTECANVAS_H
#define NOTECANVAS_H

#include "measure.h"

#include <QGraphicsItem>

class NoteCanvas : public QGraphicsItem
{
public:
    NoteCanvas(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:
    virtual void advance(int step);

private:
    QRectF rect_;
    QList<Measure*> measures_;
};

#endif // NOTECANVAS_H

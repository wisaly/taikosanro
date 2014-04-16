#ifndef NOTECANVAS_H
#define NOTECANVAS_H

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
};

#endif // NOTECANVAS_H

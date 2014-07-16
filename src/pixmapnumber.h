#ifndef PIXMAPNUMBER_H
#define PIXMAPNUMBER_H

#include <QGraphicsObject>
#include <QList>
#include "pixmapres.h"

class PixmapNumber : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PixmapNumber(const char* resKey,QGraphicsItem *parent = 0);

    void setNumber(int number);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const { return rect_; }
    void setRect(const QRectF &rect) { rect_ = rect; }

    Qt::AlignmentFlag align() const { return align_; }
    void setAlign(const Qt::AlignmentFlag &align) { align_ = align; }

signals:

public slots:

private:
    QList<PixmapRes> pixmaps_;
    Qt::AlignmentFlag align_;
    QRectF rect_;
    QList<int> digits_; // descending order
    qreal digitLength_;
};

#endif // PIXMAPNUMBER_H

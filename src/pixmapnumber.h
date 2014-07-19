#ifndef PIXMAPNUMBER_H
#define PIXMAPNUMBER_H

#include <QGraphicsObject>
#include <QList>
#include "pixmapres.h"

class PixmapNumber : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ boundingRect WRITE setRect)
public:
    explicit PixmapNumber(QGraphicsItem *parent = 0);

    void setNumber(int number);
    int addPixmapGroup(const char* resKey);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const { return rect_; }
    void setRect(const QRectF &rect);

    Qt::AlignmentFlag align() const { return align_; }
    void setAlign(const Qt::AlignmentFlag &align) { align_ = align; }

    void setCurrentGroup(int group) { group_ = group; }

signals:

public slots:

private:
    QList<QList<PixmapRes> > pixmaps_;
    Qt::AlignmentFlag align_;
    QRectF rect_;
    QList<int> digits_; // descending order
    qreal digitLength_;
    int group_;         // pixmaps group index
};

#endif // PIXMAPNUMBER_H

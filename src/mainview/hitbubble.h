#ifndef HITBUBBLE_H
#define HITBUBBLE_H

#include <QGraphicsObject>
#include "../pixmapnumber.h"

class HitBubble : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit HitBubble(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const { return backPixmap_.rect(); }

signals:

public slots:
    void consecutiveChanged(int count);
private slots:
    void animationFinished();

private:
    PixmapRes backPixmap_;
    PixmapRes textPixmap_;
    PixmapNumber *number_;
    QRectF numberRect_;
    QRectF numberScaleRect_;
};

#endif // HITBUBBLE_H

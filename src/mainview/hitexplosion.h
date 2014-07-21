#ifndef HITEXPLOSION_H
#define HITEXPLOSION_H

#include <QGraphicsObject>
#include "../pixmapres.h"
#include "../stable.h"

class HitExplosion : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit HitExplosion(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;
signals:

public slots:
    void determined(Ts::DetermineValue value);

private:
    PixmapRes basePixmap_;
    QGraphicsPixmapItem *greatItem_;
    QGraphicsPixmapItem *goodItem_;
    QRectF rect_;
};

#endif // HITEXPLOSION_H

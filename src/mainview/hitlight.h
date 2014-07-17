#ifndef HITLIGHT_H
#define HITLIGHT_H

#include <QGraphicsObject>
#include "../pixmapres.h"
#include "../stable.h"

class HitLight : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity1 READ opacity1 WRITE setOpacity1)
    Q_PROPERTY(qreal opacity2 READ opacity2 WRITE setOpacity2)
public:
    explicit HitLight(QGraphicsItem *parent = 0);

    void setCourse(const Ts::Course &course);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // property
    QRectF boundingRect() const { return rect_; }

    qreal opacity1() const { return opacity1_; }
    void setOpacity1(const qreal &opacity1) { opacity1_ = opacity1; update(); }

    qreal opacity2() const { return opacity2_; }
    void setOpacity2(const qreal &opacity2) { opacity2_ = opacity2; update(); }

signals:

public slots:
    void determined(Ts::DetermineValue value);

private:
    PixmapRes pixmap0_;
    PixmapRes pixmap1_;
    PixmapRes pixmap2_;
    Ts::Course course_;
    QRectF rect_;
    qreal opacity1_;
    qreal opacity2_;
};

#endif // HITLIGHT_H

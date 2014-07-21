#ifndef SOULGAUGE_H
#define SOULGAUGE_H

#include <QGraphicsObject>
#include "../pixmapres.h"
#include "../stable.h"

class SoulGauge : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SoulGauge(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setCourse(Ts::Course course);

    QRectF boundingRect() const { return rect_; }
signals:

public slots:
    void soulChanged(int soul);

private:
    PixmapRes forePixmap_;
    PixmapRes backPixmap_;
    QRectF rect_;
    QRectF soulUnitRect_;
    QRectF foreRect_;
};

#endif // SOULGAUGE_H

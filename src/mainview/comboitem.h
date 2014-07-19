#ifndef COMBONUMBER_H
#define COMBONUMBER_H

#include <QGraphicsObject>
#include "../pixmapnumber.h"

class ComboItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit ComboItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const { return rect_; }
signals:

public slots:
    void comboChanged(int combo);

private:
    PixmapNumber *number_;
    QRectF rect_;
    QRectF numberRect_;
    QRectF numberScaleRect_;
};

#endif // COMBONUMBER_H

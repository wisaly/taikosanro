#ifndef MEASURE_H
#define MEASURE_H

#include <QGraphicsItem>

class Measure : public QGraphicsItem
{
public:
    Measure(QGraphicsItem *parent = 0);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:
    void advance(int step);

private:
    QRectF canvasRect;
};
#endif // MEASURE_H

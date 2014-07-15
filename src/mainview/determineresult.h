#ifndef DETERMINERESULT_H
#define DETERMINERESULT_H

#include <QElapsedTimer>
#include <QGraphicsObject>
#include <QStateMachine>

#include "determinerange.h"
#include "../pixmapres.h"

class DetermineResult : public QGraphicsObject
{
    Q_OBJECT
public:
    DetermineResult(QGraphicsItem *parent = 0);

    QRectF boundingRect() const { return rect_; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);
    void advance(int step);

public slots:
    void determined(Ts::DetermineValue value);
private:
    Ts::DetermineValue result_;
    QRectF rect_;
    QPointF pos1_;
    QPointF pos2_;
    PixmapRes greatPixmap_;
    PixmapRes goodPixmap_;
    PixmapRes failPixmap_;
};

#endif // DETERMINERESULT_H

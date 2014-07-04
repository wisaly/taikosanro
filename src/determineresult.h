#ifndef DETERMINERESULT_H
#define DETERMINERESULT_H

#include <QElapsedTimer>
#include <QGraphicsItem>

#include "determinerange.h"

class DetermineResult : public QGraphicsItem
{
public:
    DetermineResult(QGraphicsItem *parent);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);
    virtual void advance(int step);

    void showResult(Ts::DetermineValue result);
private:
    Ts::DetermineValue result_;
    bool isShow_;
    QElapsedTimer startShow_;
};

#endif // DETERMINERESULT_H

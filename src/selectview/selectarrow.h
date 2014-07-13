#ifndef SELECTARROW_H
#define SELECTARROW_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QMap>
#include "../stable.h"

class SelectArrow : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SelectArrow(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addSelection(Ts::Course course, QPointF pos);
    Ts::Course selection() const { return selections_[current_].first; }
    void moveSelection(int step);
signals:

public slots:

private:
    QPixmap arrowPixmap_;
    QList<QPair<Ts::Course,QPointF> > selections_;
    int current_;
};

#endif // SELECTARROW_H

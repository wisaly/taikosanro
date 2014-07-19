#ifndef COMBOBUBBLE_H
#define COMBOBUBBLE_H

#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include "../pixmapnumber.h"

class ComboBubble : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal backScale READ backScale WRITE setBackScale)
public:
    explicit ComboBubble(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const { return backItem_->boundingRect(); }

    qreal backScale() { return backItem_->scale(); }
    void setBackScale(qreal scale) { backItem_->setScale(scale); }
signals:

public slots:
    void comboChanged(int combo);

private slots:
    void animationFinished();

private:
    QGraphicsPixmapItem *backItem_;
    QGraphicsPixmapItem *breakItem_;
    PixmapNumber *number_;
};

#endif // COMBOBUBBLE_H

#ifndef SELECTCANVAS_H
#define SELECTCANVAS_H

#include <QGraphicsObject>
#include <QList>
#include "selectitem.h"

class SelectCanvas : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SelectCanvas(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void setRect(const QRectF &rect){rect_ = rect;}

    SelectItem *addItem();
    void calcPos();
    void move(int step);

signals:

public slots:

private:
    QRectF rect_;
    QList<SelectItem*> items_;
    int currentItem_;
};

#endif // SELECTCANVAS_H

#ifndef SELECTCANVAS_H
#define SELECTCANVAS_H

#include <QGraphicsObject>
#include <QList>
#include "dirloader.h"
#include "selectitem.h"

class SelectCanvas : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SelectCanvas(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void setRect(const QRectF &rect){rect_ = rect;}

    void load();
    SelectItem *itemAt(int index);

    void move(int step);
    void expand();

    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void moveFinished();
private:
    DirLoader loader_;
    QRectF rect_;
    QList<SelectItem*> items_;
    int current_;
    QRectF barRect_;
    QRectF barExpandRect_;
    QRectF barContentRect_;
};

#endif // SELECTCANVAS_H

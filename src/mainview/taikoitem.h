#ifndef TAIKOITEM_H
#define TAIKOITEM_H

#include <QElapsedTimer>
#include <QGraphicsObject>
#include "../pixmapres.h"
#include "../stable.h"

class TaikoItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TaikoItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const { return backPixmap_.rect(); }

    void advance(int phase);
signals:

public slots:
    void hit(Ts::TaikoState state);
private:
    PixmapRes backPixmap_;
    PixmapRes donLPixmap_;
    PixmapRes donRPixmap_;
    PixmapRes kaLPixmap_;
    PixmapRes kaRPixmap_;
    QElapsedTimer donLBegin_;
    QElapsedTimer donRBegin_;
    QElapsedTimer kaLBegin_;
    QElapsedTimer kaRBegin_;
    int delayState_;
};

#endif // TAIKOITEM_H

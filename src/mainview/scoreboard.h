#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsObject>
#include "../pixmapnumber.h"

class ScoreBoard : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit ScoreBoard(QGraphicsItem *parent = 0);

    QRectF boundingRect() const { return rect_; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:

public slots:
    void scoreAdded(int delta);
    void scoreChanged(int score);

private:
    PixmapNumber *total_;
    PixmapNumber *add_;
    QRectF rect_;
    QRectF totalRect_;
    QRectF totalScaleRect_;
    QRectF addRect_;
};

#endif // SCOREBOARD_H

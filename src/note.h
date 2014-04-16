#ifndef NOTE_H
#define NOTE_H

#include "determinerange.h"
#include <QGraphicsItem>

class Note : public QGraphicsItem
{
public:
    enum Type{
        RedMarker,
        BlueMarker,
        BigRedMarker,
        BigBlueMarker,
        YellowBar,
        Ballon,
        Yam
    };

    explicit Note(Type noteType,QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:
    void advance(int step);

private:
    Type noteType;
    QPixmap notePixmap;
    DetermineRange determineRange;
};

#endif // NOTE_H

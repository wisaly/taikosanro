#ifndef NOTE_H
#define NOTE_H

#include "determinerange.h"
#include <QGraphicsItem>

class Note : public QGraphicsItem
{
public:
    enum Type{
        Blank,
        RedMarker,
        BlueMarker,
        BigRedMarker,
        BigBlueMarker,
        YellowBar,
        BigYellowBar,
        Ballon,
        EndYellowBar,
        Yam,
    };

    explicit Note(Type noteType_,int index,QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int index();

protected:
    void advance(int step);

private:
    Type noteType_;
    QPixmap notePixmap_;
    DetermineRange determineRange_;
    int index_;
};

typedef QList<Note::Type> NoteTypeList;

#endif // NOTE_H

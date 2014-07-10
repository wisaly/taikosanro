#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsItem>
#include <QObject>
#include "determinerange.h"
#include "stable.h"

class Note : public QGraphicsItem//,public QObject
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

   explicit Note(QGraphicsItem *parent,Type noteType,int index);

   virtual QRectF boundingRect() const;
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    int index();
    void setDetermineTime(int elapsed);
    Ts::DetermineValue determine(int elapsed);
    void moveOut(Ts::DetermineValue value);

    virtual bool acceptAct(Ts::TaikoState action);
    virtual void setUnitWidth(int unitWidth);

protected:
    virtual void advance(int step);

protected:
    Type noteType_;
    QPixmap notePixmap_;
    DetermineRange determineRange_;
    int index_;
    int unitWidth_;     // actual width of a note unit
};

typedef QList<Note::Type> NoteTypeList;

#endif // NOTE_H

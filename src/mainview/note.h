#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsObject>
#include "determinerange.h"
#include "../pixmapres.h"
#include "../stable.h"

class Note : public QGraphicsObject
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

   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    int index();
    void setDetermineTime(int elapsed) { determineRange_.setRange(elapsed); }
    virtual Ts::DetermineValue determine(int elapsed) { return determineRange_.determine(elapsed); }

    virtual bool acceptAct(Ts::TaikoState action);
    virtual bool isBigNote();
    virtual void setUnitSize(int unitWidth,int unitHeight);

protected:
    void advance(int phase);

protected:
    Type noteType_;
    PixmapRes notePixmap_;
    DetermineRange determineRange_;
    int index_;
    int unitWidth_;     // actual width of a note unit
    int unitHeight_;
    QRectF rect_;
};

typedef QList<Note::Type> NoteTypeList;

#endif // NOTE_H

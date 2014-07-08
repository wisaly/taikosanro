#ifndef NOTEYELLOWBAR_H
#define NOTEYELLOWBAR_H

#include "note.h"

class NoteYellowBar : public Note
{
public:
    NoteYellowBar(QGraphicsItem *parent,int index,bool isBig,int length);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int length() const;

    int hitCount() const;
    void setHitCount(int hitCount);

    virtual bool acceptAct(Ts::TaikoState action);

    //virtual void setUnitWidth(int unitWidth);

protected:
    int length_;
    int hitCount_;
    QPixmap noteHeadPixmap_;
    QPixmap noteTailPixmap_;
};

#endif // NOTEYELLOWBAR_H

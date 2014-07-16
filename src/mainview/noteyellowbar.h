#ifndef NOTEYELLOWBAR_H
#define NOTEYELLOWBAR_H

#include <QDebug>
#include "note.h"

class NoteYellowBar : public Note
{
public:
    NoteYellowBar(QGraphicsItem *parent,int index,bool isBig);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int length() const { return length_; }
    void setLength(int length,int timeLength) { length_ = length; timeLength_ = timeLength; qDebug() << timeLength; }

    int hitCount() const { return hitCount_; }
    void setHitCount(int hitCount) { hitCount_ = hitCount; }

    Ts::DetermineValue determine(int elapsed);

    bool acceptAct(Ts::TaikoState action);

    void setUnitWidth(int unitWidth);

private:
    int length_;
    int timeLength_;
    int hitCount_;
    PixmapRes headPixmap_;
    PixmapRes tailPixmap_;
};

#endif // NOTEYELLOWBAR_H

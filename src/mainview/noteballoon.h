#ifndef NOTEBALLON_H
#define NOTEBALLON_H

#include "note.h"

class NoteBalloon : public Note
{
public:
    NoteBalloon(QGraphicsItem *parent,int index);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int length() const { return length_; }
    void setLength(int length,int timeLength) { length_ = length; timeLength_ = timeLength; }

    int hitCount() const { return hitCount_; }
    void setHitCount(int hitCount) { hitCount_ = hitCount; }

    int count() const { return count_; }
    void setCount(int count) { count_ = count; }

    bool acceptAct(Ts::TaikoState action);

    Ts::DetermineValue determine(int elapsed);
protected:
    int count_;
    int hitCount_;
    int length_;
    int timeLength_;
};

#endif // NOTEBALLON_H

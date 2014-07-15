#ifndef NOTEBALLON_H
#define NOTEBALLON_H

#include "note.h"

class NoteBallon : public Note
{
public:
    NoteBallon(QGraphicsItem *parent,int index);

    int length() const { return length_; }
    void setLength(int length) { length_ = length; }

    int hitCount() const { return hitCount_; }
    void setHitCount(int hitCount) { hitCount_ = hitCount; }

    int count() const { return count_; }
    void setCount(int count) { count_ = count; }

    bool acceptAct(Ts::TaikoState action);

protected:
    int count_;
    int hitCount_;
    int length_;
};

#endif // NOTEBALLON_H

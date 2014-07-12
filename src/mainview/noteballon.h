#ifndef NOTEBALLON_H
#define NOTEBALLON_H

#include "note.h"

class NoteBallon : public Note
{
public:
    NoteBallon(QGraphicsItem *parent,int index,int count);

    int hitCount() const;
    void setHitCount(int hitCount);

    int count() const;
    void setCount(int count);

    bool acceptAct(Ts::TaikoState action);

protected:
    int count_;
    int hitCount_;
};

#endif // NOTEBALLON_H

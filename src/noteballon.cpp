#include "noteballon.h"

NoteBallon::NoteBallon(QGraphicsItem *parent, int index, int count)
    :Note(parent,Note::Ballon,index),count_(count),hitCount_(0)
{
}
int NoteBallon::hitCount() const
{
    return hitCount_;
}

void NoteBallon::setHitCount(int hitCount)
{
    hitCount_ = hitCount;
}
int NoteBallon::count() const
{
    return count_;
}

void NoteBallon::setCount(int count)
{
    count_ = count;
}



#include "noteballon.h"

NoteBallon::NoteBallon(QGraphicsItem *parent, int index)
    :Note(parent,Note::Ballon,index),
      count_(0),
      hitCount_(0)
{
}

bool NoteBallon::acceptAct(Ts::TaikoState action)
{
    return action & Ts::DON_BOTH;
}



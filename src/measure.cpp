#include "measure.h"
#include <QDebug>

Measure::Measure(QGraphicsItem *parent,
                 NoteTypeList &notes,
                 qreal tempo,
                 int noteValuePerBeat,
                 int beatsPerBar)
    :QGraphicsItem(parent),
      tempo_(tempo),
      noteValuePerBeat_(noteValuePerBeat),
      beatsPerBar_(beatsPerBar)
{
    Q_ASSERT(parent != 0);

    canvasRect_ = parent->boundingRect();

    notePosCount_ = notes.count();
    for(int i = 0;i < notes.count();i++)
    {
        if(notes[i] == Note::Blank)
        {
            continue;
        }

        Note *note = new Note(notes[i],i,this);
        notes_.append(note);
    }
}

QRectF Measure::boundingRect() const
{
    return canvasRect_;
}

void Measure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void Measure::calcPos(int currentElapsed)
{
    qreal offset = tempo_ * currentElapsed * canvasRect_.width() / (notePosCount_ * 60000);

    //qDebug() << offset;
    //prepareGeometryChange();
    //canvasRect_.moveLeft(canvasRect_.width() - offset);
    setPos(canvasRect_.width() - offset,0);
}

int Measure::appearElapsed()
{
    return appearElapsed_;
}

void Measure::setBoundingRect(QRectF rect)
{
    canvasRect_ = rect;
    qreal noteUnit = canvasRect_.width() / notePosCount_;
    for(int i = 0;i < notes_.count();i++)
    {
        notes_[i]->setPos(notes_[i]->index() * noteUnit,0);
        notes_[i]->setZValue(notes_.count() - i);
    }
}

void Measure::advance(int step)
{

}

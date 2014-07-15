#include "measure.h"
#include "noteballon.h"
#include "noteyellowbar.h"
#include "../stable.h"
#include <QDebug>
#include <QPainter>

Measure::Measure(QGraphicsItem *parent)
    :QGraphicsItem(parent),
      tempo_(0),
      noteValuePerBeat_(0),
      beatsPerBar_(0),
      isGGT_(false),
      appearElapsed_(0)
{
    setVisible(false);
    setCacheMode(ItemCoordinateCache);

    //setBoundingRect(parent->boundingRect());
}

Measure::~Measure()
{
    clear();
}

void Measure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawLine(Ts::NOTE_WIDTH / 2,0,Ts::NOTE_WIDTH / 2, Ts::NOTE_HEIGHT);
}

void Measure::reset()
{
    setPos(canvasRect_.width(),0);
}

void Measure::calcPos(int currentElapsed)
{
    qreal offset = (currentElapsed - appearElapsed_)
            * tempo_ * canvasRect_.width() / (beatsPerBar_ * 60000);

    //qDebug() << canvasRect_.width() - pos().x() - offset << appearElapsed_;
    setPos(canvasRect_.width() - offset,0);
}



void Measure::setBoundingRect(QRectF rect)
{
    canvasRect_ = rect;
    qreal unitWidth = canvasRect_.width() / noteUnitCount_;

    for(int i = 0;i < notes_.count();i++)
    {
        notes_[i]->setPos(notes_[i]->index() * unitWidth,0);
        notes_[i]->setUnitWidth(unitWidth);
    }
}

void Measure::clear()
{
    for (int i = 0;i < notes_.count();i++)
    {
        delete notes_[i];
    }
    notes_.clear();
}

void Measure::setNotes(NoteTypeList notes, QQueue<int> &ballonHits,QQueue<int> &ballonLen, QQueue<int> &yellowbarLen)
{
    notes_.clear();

    noteUnitCount_ = notes.count();

    for(int i = 0;i < notes.count();i++)
    {
        Note *note = 0;
        if (notes[i] == Note::Blank)
        {
            continue;
        }
        else if (notes[i] == Note::YellowBar || notes[i] == Note::BigYellowBar)
        {
            if (yellowbarLen.empty())
                continue;

            note = new NoteYellowBar(
                        this,
                        i,
                        notes[i] == Note::BigYellowBar);
            static_cast<NoteYellowBar*>(note)->setLength(
                        yellowbarLen.dequeue());
        }
        else if (notes[i] == Note::Ballon)
        {
            if (ballonHits.empty() || ballonLen.empty())
                continue;

            note = new NoteBallon(this,i);
            static_cast<NoteBallon*>(note)->setCount(
                        ballonHits.dequeue());
            static_cast<NoteBallon*>(note)->setLength(
                        ballonLen.dequeue());
        }
        else
        {
            note = new Note(this,notes[i],i);
        }

        note->setDetermineTime(
                    appearElapsed_ +
                    60000.0 / tempo_ * beatsPerBar_ +
                    i * 60000.0 * beatsPerBar_ / noteUnitCount_ / tempo_);

        note->setZValue(-1 * i);
        if (note != 0)
        {
            notes_.append(note);
        }
    }

    // roughly set beats per bar + 1
    disappearElapsed_ = appearElapsed_ + 60000 / tempo_ * (beatsPerBar_ * 2 + 1);
}

void Measure::advance(int phase)
{
    Q_UNUSED(phase);
}

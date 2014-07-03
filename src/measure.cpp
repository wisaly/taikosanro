#include "measure.h"
#include "noteballon.h"
#include "noteyellowbar.h"
#include "stable.h"
#include <QDebug>
#include <QPainter>

Measure::Measure(QGraphicsItem *parent,
                 NoteTypeList &notes,
                 QList<int> &ballonHits,
                 qreal tempo,
                 int noteValuePerBeat,
                 int beatsPerBar, bool isGGT, int appearElapsed)
    :QGraphicsItem(parent),
      tempo_(tempo),
      noteValuePerBeat_(noteValuePerBeat),
      beatsPerBar_(beatsPerBar),
      isGGT_(isGGT),
      appearElapsed_(appearElapsed)
{
    Q_ASSERT(parent != 0);
    setVisible(false);
    setCacheMode(ItemCoordinateCache);

    canvasRect_ = parent->boundingRect();

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
            for (int j = i;j < notes.count();j++)
            {
                if (notes[j] == Note::EndYellowBar)
                {
                    note = new NoteYellowBar(this,i,notes[i] == Note::BigYellowBar,j - i + 1);
                    i = j;
                    break;
                }
            }
        }
        else if (notes[i] == Note::Ballon)
        {
            if (!ballonHits.empty())
            {
                note = new NoteBallon(this,i,ballonHits.takeFirst());
            }
        }
        else
        {
            note = new Note(this,notes[i],i);
        }

        note->setZValue(-1 * i);
        if (note != 0)
        {
            notes_.append(note);
        }
    }

    disappearElapsed_ = appearElapsed_ + 60000 / tempo_ * beatsPerBar_ * 2;
}

QRectF Measure::boundingRect() const
{
    return canvasRect_;
}

void Measure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawLine(NOTE_WIDTH / 2,0,NOTE_WIDTH / 2, NOTE_HEIGHT);
}

void Measure::calcPos(int currentElapsed)
{
    qreal offset = (currentElapsed - appearElapsed_)
            * tempo_ * canvasRect_.width() / (beatsPerBar_ * 60000);

    //qDebug() << appearElapsed_ << canvasRect_.width() - pos().x() - offset;

    setPos(canvasRect_.width() - offset,0);
}

int Measure::appearElapsed()
{
    return appearElapsed_;
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

void Measure::advance(int step)
{
    Q_UNUSED(step);
}
int Measure::disappearElapsed() const
{
    return disappearElapsed_;
}


#include "measure.h"
#include "noteballon.h"
#include "noteyellowbar.h"
#include <QDebug>

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

        if (note != 0)
        {
            notes_.append(note);
        }
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
    qreal offset = tempo_ * (currentElapsed - appearElapsed_) * canvasRect_.width() / (beatsPerBar_ * 60000);

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
    qreal unitWidth = canvasRect_.width() / noteUnitCount_;
    //setTransformOriginPoint(unitWidth / 2,0);

    for(int i = 0;i < notes_.count();i++)
    {
        notes_[i]->setPos(notes_[i]->index() * unitWidth,0);
        notes_[i]->setZValue(notes_.count() - i);
        notes_[i]->setUnitWidth(unitWidth);
    }
}

void Measure::advance(int step)
{

}

#include <QDebug>
#include <QPainter>
#include "notechart.h"
#include "../pixmapmanager.h"

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsObject(parent),
      isPlaying_(false)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

    noteRect_ = QRectF(
                PixmapManager::getPos(Ts::mv::NOTE_POS),
                PixmapManager::getSize(Ts::mv::NOTE_SIZE));
}

QRectF NoteChart::boundingRect() const
{
    return rect_;
}

void NoteChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(rect_);
}

void NoteChart::play()
{
    if (isPlaying_)
    {
        isPlaying_ = false;
    }
    else
    {
        reset();
        currentMeasure_ = 0;
        detMeasure_ = 0;
        detNote_ = 0;
        score_.init(scoreInit_,scoreDiff_);
        playProgress_.start();
        isPlaying_ = true;

        // move determine pointer to valid note
        hit(Ts::NO_ACT);
    }
}

void NoteChart::hit(Ts::TaikoState state)
{
    if (!isPlaying_)
    {
        return;
    }

    // move to next valid measure & note
    while (detMeasure_ < measures_.count())
    {
        // move to next measure
        if (detNote_ >= measures_[detMeasure_]->noteCount())
        {
            detMeasure_++;
            detNote_ = 0;
            continue;
        }
        else
        {
            break;
        }
    }

    if (detMeasure_ >= measures_.count())
    {
        return;
    }

    Note *note = measures_[detMeasure_]->noteAt(detNote_);
    Ts::DetermineValue result = note->determine(playProgress_.elapsed());

    bool isBigNote = false;

    // hit determine
    if (state & Ts::DON_BOTH || state & Ts::KA_BOTH)
    {
        if (!note->acceptAct(state))
            return;

        if (result == Ts::GREAT || result == Ts::GOOD || result == Ts::FAIL)
        {
            detNote_++;
            emit determined(result);

            // note is big note & hit both side
            if (note->isBigNote() &&
                    ((state & Ts::DON_BOTH) == Ts::DON_BOTH ||
                    (state & Ts::KA_BOTH) == Ts::KA_BOTH))
            {
                isBigNote = true;
            }

            // hide
            note->hide();
        }
        else if (result == Ts::CONSECUTIVE_HIT)
        {
            // note is big note
            isBigNote = note->isBigNote();
        }
        else if (result == Ts::CONSECUTIVE_OVER)
        {
            note->hide();
            detNote_++;
        }
    }
    else
    {
        // miss determine
        if (result == Ts::MISS)
        {
            detNote_++;
            emit determined(Ts::MISS);
        }
        else if (result == Ts::PASS)
        {
            detNote_++;
        }
    }

    score_.add(result,isBigNote,measures_[detMeasure_]->isGGT());
}

void NoteChart::setBoundingRect(QRectF rect)
{
    rect_ = rect;

    for (int i = 0;i < measures_.count();i++)
    {
        measures_[i]->setBoundingRect(rect);
    }
}

void NoteChart::reset()
{
    for (int i = 0;i < measures_.count();i++)
    {
        measures_[i]->reset();
    }
}

Measure *NoteChart::createMeasure()
{
    Measure *measure = new Measure(this);
    measure->setZValue(-1 * measures_.count());
    measure->setNoteRect(noteRect_);
    measures_.append(measure);

    return measure;
}

void NoteChart::clear()
{
    for (int i = 0;i < measures_.count();i++)
    {
        delete measures_[i];
    }
    measures_.clear();
}

void NoteChart::advance(int phase)
{
    if (!isPlaying_)
    {
        return ;
    }
    if (phase)
    {
        int currentElapsed = playProgress_.elapsed();

        // hide disappear measure
        while (currentMeasure_ >= 0 && currentMeasure_ < measures_.count() &&
               currentElapsed > measures_[currentMeasure_]->disappearElapsed())
        {
            measures_[currentMeasure_]->hide();
            currentMeasure_++;
        }

        if (currentMeasure_ >= measures_.count())
        {
            return;
        }

        for (int i = currentMeasure_;i < measures_.count();i++)
        {
            if (currentElapsed >= measures_[i]->appearElapsed())
            {
                measures_[i]->show();
                measures_[i]->calcPos(currentElapsed);
            }
            else
            {
                break;
            }
        }
        //qDebug() << currentElapsed << "end" << playProgress_.elapsed() - currentElapsed;

        hit(Ts::NO_ACT);
    }
}

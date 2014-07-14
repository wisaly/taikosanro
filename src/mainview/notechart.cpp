#include "notechart.h"
#include <QDebug>
#include <QPainter>

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsObject(parent),isPlaying_(false)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

    if (parent != 0)
    {
        setBoundingRect(parent->boundingRect());
    }
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
        currentMeasure_ = -1;
        detMeasure_ = 0;
        detNote_ = 0;
        playProgress_.start();
        isPlaying_ = true;
    }
}

void NoteChart::hit(Ts::TaikoState state)
{
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

    // hit determine
    if (state & Ts::DON_BOTH || state & Ts::KA_BOTH)
    {
        if (detMeasure_ >= measures_.count())
        {
            return;
        }

        if (!measures_[detMeasure_]->noteAt(detNote_)->acceptAct(state))
            return;

        Ts::DetermineValue result = measures_[detMeasure_]->noteAt(detNote_)->determine(playProgress_.elapsed());
        if (result == Ts::OUTSIDE || result == Ts::MISS)
            return;

        measures_[detMeasure_]->noteAt(detNote_)->moveOut(result);
        detNote_++;
        emit determined(result);
    }
    else
    {
        // miss determine
        if (measures_[detMeasure_]->noteAt(detNote_)->determine(playProgress_.elapsed()) == Ts::MISS)
        {
            detNote_++;
            emit determined(Ts::MISS);
        }
    }
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

Measure *NoteChart::createMeasure(NoteTypeList &notes, QQueue<int> &ballonHits, qreal tempo, int noteValuePerBeat, int beatsPerBar, bool isGGT, int appearElapsed)
{
    Measure *measure = new Measure(this,notes,ballonHits,tempo,noteValuePerBeat,beatsPerBar,isGGT,appearElapsed);
    measure->setZValue(-1 * measures_.count());
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

void NoteChart::advance(int step)
{
    if (!isPlaying_)
    {
        return ;
    }
    if (step)
    {
        int currentElapsed = playProgress_.elapsed();
        static int last = 0;
        if (last == 0)
            last = currentElapsed;
        else
        {
            qDebug() << "delta:" << currentElapsed - last;
            last = currentElapsed;
        }
        // hide disappear measure
        if (currentMeasure_ > 0 && currentElapsed > measures_[currentMeasure_]->disappearElapsed())
        {
            measures_[currentMeasure_]->setVisible(false);
        }

        // change current measure and show
        if (currentMeasure_ + 1 < measures_.count() &&
                currentElapsed >= measures_[currentMeasure_ + 1]->appearElapsed())
        {
            currentMeasure_++;
            measures_[currentMeasure_]->setVisible(true);
        }

        // current measure position
        if (currentMeasure_ >= 0)
        {
            measures_[currentMeasure_]->calcPos(currentElapsed);
        }
        // previous measure position
        if (currentMeasure_ > 0)
        {
            measures_[currentMeasure_ - 1]->calcPos(currentElapsed);
        }
        // previous previous measure position
        if (currentMeasure_ > 1)
        {
            measures_[currentMeasure_ - 2]->calcPos(currentElapsed);
        }
        //qDebug() << currentElapsed << "end" << playProgress_.elapsed() - currentElapsed;

        hit(Ts::NO_ACT);
    }
}

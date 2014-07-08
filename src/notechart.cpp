#include "notechart.h"
#include <QDebug>
#include <QPainter>

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsItem(parent),isPlaying_(false)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

    if (parent != 0)
    {
        this->setBoundingRect(parent->boundingRect());
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
        detMeasureDon_ = 0;
        detMeasureKa_ = 0;
        detNoteDon_ = 0;
        detNoteKa_ = 0;
        playProgress_.start();
        isPlaying_ = true;
    }
}

Ts::DetermineValue NoteChart::hitTest(Ts::TaikoState state)
{
    // move to next valid measure & note
    while (detMeasureDon_ < measures_.count())
    {
        // move to next measure
        if (detNoteDon_ >= measures_[detMeasureDon_]->noteCount())
        {
            detMeasureDon_++;
            detNoteDon_ = 0;
            continue;
        }

        // move to next acceptable note
        while (detNoteDon_ < measures_[detMeasureDon_]->noteCount())
        {
            if (!measures_[detMeasureDon_]->noteAt(detNoteDon_)->acceptAct(Ts::DON_BOTH))
                detNoteDon_++;
            else
                break;
        }
        if (detNoteDon_ < measures_[detMeasureDon_]->noteCount())
            break;
    }

    while (detMeasureKa_ < measures_.count())
    {
        if (detNoteKa_ >= measures_[detMeasureKa_]->noteCount())
        {
            detMeasureKa_++;
            detNoteKa_ = 0;
            continue;
        }

        while (detNoteKa_ < measures_[detMeasureKa_]->noteCount())
        {
            if (!measures_[detMeasureKa_]->noteAt(detNoteKa_)->acceptAct(Ts::KA_BOTH))
                detNoteKa_++;
            else
                break;
        }
        if (detNoteKa_ < measures_[detMeasureKa_]->noteCount())
            break;
    }

    if(state != Ts::NO_ACT)
        qDebug() << detMeasureDon_ << detNoteDon_ << detMeasureKa_ << detNoteKa_;

    // hit determine
    if (state & Ts::DON_BOTH)
    {
        if (detMeasureDon_ >= measures_.count())
            return Ts::OUTSIDE;

        Ts::DetermineValue result = measures_[detMeasureDon_]->noteAt(detNoteDon_)->determine(playProgress_.elapsed());
        if (result == Ts::OUTSIDE)
            return Ts::OUTSIDE;

        measures_[detMeasureDon_]->noteAt(detNoteDon_)->hide();
        detNoteDon_++;
        return result;
    }
    else if (state & Ts::KA_BOTH)
    {
        if (detMeasureKa_ >= measures_.count())
            return Ts::OUTSIDE;

        Ts::DetermineValue result = measures_[detMeasureKa_]->noteAt(detNoteKa_)->determine(playProgress_.elapsed());
        if (result == Ts::OUTSIDE)
            return Ts::OUTSIDE;

        measures_[detMeasureKa_]->noteAt(detNoteKa_)->hide();
        detNoteKa_++;
        return result;
    }
    else
    {
        // miss determine
        if (detMeasureDon_ > detMeasureKa_ ||
                (detMeasureDon_ == detMeasureKa_ && detNoteDon_ > detNoteKa_))
        {
            if (measures_[detMeasureDon_]->noteAt(detNoteDon_)->determine(playProgress_.elapsed()) == Ts::MISS)
            {
                detNoteDon_++;
                return Ts::MISS;
            }
        }
        else
        {
            if (measures_[detMeasureKa_]->noteAt(detNoteKa_)->determine(playProgress_.elapsed()) == Ts::MISS)
            {
                detNoteKa_++;
                return Ts::MISS;
            }
        }
    }

    return Ts::OUTSIDE;
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

int NoteChart::measureCount()
{
    return measures_.count();
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
        //qDebug() << currentElapsed << "begin";
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
    }
}
int NoteChart::scoreDiff() const
{
    return scoreDiff_;
}

void NoteChart::setScoreDiff(int scoreDiff)
{
    scoreDiff_ = scoreDiff;
}

int NoteChart::scoreInit() const
{
    return scoreInit_;
}

void NoteChart::setScoreInit(int scoreInit)
{
    scoreInit_ = scoreInit;
}

int NoteChart::course() const
{
    return course_;
}

void NoteChart::setCourse(int course)
{
    course_ = course;
}

int NoteChart::level() const
{
    return level_;
}

void NoteChart::setLevel(int level)
{
    level_ = level;
}


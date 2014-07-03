#include "notechart.h"
#include <QDebug>
#include <QPainter>

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsItem(parent),isPlaying_(false)
{
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);
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
        playProgress_.start();
        isPlaying_ = true;
    }
}

void NoteChart::hit(TaikoState state)
{
    Q_UNUSED(state);
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
        measures_[i]->calcPos(measures_[i]->appearElapsed());
    }
}

Measure *NoteChart::createMeasure(NoteTypeList &notes, QList<int> &ballonHits, qreal tempo, int noteValuePerBeat, int beatsPerBar, bool isGGT, int appearElapsed)
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


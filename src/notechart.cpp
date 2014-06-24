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
    painter->drawRect(rect_);
}

void NoteChart::play()
{
    currentMeasure_ = -1;
    playProgress_.start();
    isPlaying_ = true;
}

void NoteChart::hit(TaikoState state)
{

}

void NoteChart::setBoundingRect(QRectF rect)
{
    rect_ = rect;

    for (int i = 0;i < measures_.count();i++)
    {
        measures_[i]->setBoundingRect(rect);
    }
}

Measure *NoteChart::createMeasure(NoteTypeList &notes, qreal tempo, int noteValuePerBeat, int beatsPerBar)
{
    Measure *measure = new Measure(this,notes,tempo,noteValuePerBeat,beatsPerBar);
    measures_.append(measure);

    return measure;
}

void NoteChart::advance(int step)
{
    if (!isPlaying_)
    {
        return ;
    }
    if (step)
    {
        if (currentMeasure_ + 1 < measures_.count() &&
                playProgress_.elapsed() >= measures_[currentMeasure_ + 1]->appearElapsed())
        {
            if (currentMeasure_ >= 0)
            {
                measures_[currentMeasure_]->setVisible(false);
            }
            currentMeasure_++;
            measures_[currentMeasure_]->setVisible(true);
        }

        if (currentMeasure_ >= 0 && currentMeasure_ < measures_.count())
        {
            measures_[currentMeasure_]->calcPos(playProgress_.elapsed());
        }
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


#include "notechart.h"
#include <QDebug>

NoteChart::NoteChart(QGraphicsItem *parent)
    :QGraphicsItem(parent),rect_(0,0,700,100)
{
}

QRectF NoteChart::boundingRect() const
{
    return rect_;
}

void NoteChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void NoteChart::play()
{
    currentMeasure_ = -1;
    playProgress_.start();
}

void NoteChart::hit(TaikoState state)
{

}

Measure *NoteChart::createMeasure(NoteTypeList &notes, qreal tempo, int noteValuePerBeat, int beatsPerBar)
{
    Measure *measure = new Measure(this,notes,tempo,noteValuePerBeat,beatsPerBar);
    measures_.append(measure);

    return measure;
}

void NoteChart::advance(int step)
{
    if (step)
    {
        if (currentMeasure_ + 1 < measures_.count() &&
                playProgress_.elapsed() >= measures_[currentMeasure_ + 1])
        {
            currentMeasure_++;
            measures_[currentMeasure_]->setVisible(true);
        }
    }
}

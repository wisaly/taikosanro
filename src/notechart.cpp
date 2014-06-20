#include "notechart.h"

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
    currentMeasure_ = 0;
    playProgress_ = 0;
}

void NoteChart::hit(TaikoState state)
{

}

Measure *NoteChart::createMeasure(NoteTypeList &notes, qreal tempo, int noteValuePerBeat, int beatsPerBar)
{
    Measure *measure = new Measure(parent,notes,tempo,noteValuePerBeat,beatsPerBar);
    measures_.append(measure);
}

void NoteChart::advance(int step)
{
    
}

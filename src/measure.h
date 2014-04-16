#ifndef MEASURE_H
#define MEASURE_H

#include "note.h"

#include <QGraphicsItem>

class Measure : public QGraphicsItem
{
public:
    Measure(QGraphicsItem *parent,
            NoteTypeList &notes,
            qreal tempo,
            int noteValuePerBeat,
            int beatsPerBar);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:
    void advance(int step);

private:
    QRectF canvasRect_;
    QList<Note*> notes_;
    qreal tempo_;
    int noteValuePerBeat_;
    int beatsPerBar_;

    quint64 appearElapsed_;
};
#endif // MEASURE_H

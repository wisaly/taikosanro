#ifndef MEASURE_H
#define MEASURE_H

#include "note.h"

#include <QGraphicsItem>
#include <QQueue>

class Measure : public QGraphicsItem
{
public:
    Measure(QGraphicsItem *parent,
            NoteTypeList &notes,
            QQueue<int> &ballonHits,
            qreal tempo,
            int noteValuePerBeat,
            int beatsPerBar,
            bool isGGT,
            int appearElapsed);
    ~Measure();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void reset();
    void calcPos(int currentElapsed);
    int appearElapsed();
    void setBoundingRect(QRectF rect);

    int disappearElapsed() const;
    int noteCount();
    Note *noteAt(int index);
    void clear();

protected:
    virtual void advance(int step);

private:
    QRectF canvasRect_;
    QList<Note*> notes_;
    qreal tempo_;
    int noteValuePerBeat_;
    int beatsPerBar_;
    int noteUnitCount_;
    bool isGGT_;

    int appearElapsed_;
    int disappearElapsed_;
};
#endif // MEASURE_H

#ifndef NOTECHART_H
#define NOTECHART_H

#include "measure.h"
#include "stable.h"

#include <QElapsedTimer>
#include <QGraphicsItem>

class NoteChart : public QGraphicsItem
{
public:
    NoteChart(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void play();
    void hit(TaikoState state);
    void setBoundingRect(QRectF rect);

    Measure* createMeasure(NoteTypeList &notes,
                           qreal tempo,
                           int noteValuePerBeat,
                           int beatsPerBar);
protected:
    void advance(int step);

private:
    QString course_;
    int level_;
    int scoreInit_;
    int scoreDiff_;
    QRectF rect_;
    QList<Measure*> measures_;
    int currentMeasure_;
    //int playProgress_;
    QElapsedTimer playProgress_;
};

#endif // NOTECHART_H

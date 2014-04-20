#ifndef NOTECHART_H
#define NOTECHART_H

#include "measure.h"

#include <QGraphicsItem>

class NoteChart : public QGraphicsItem
{
public:
    NoteChart(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void addMeasure(Measure* measure);
    
protected:
    void advance(int step);

private:
    QString course_;
    int level_;
    int scoreInit_;
    int scoreDiff_;
    QRectF rect_;
    QList<Measure*> measures_;
};

#ENDIF // NOTECHART_H

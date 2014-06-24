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
    int level() const;
    void setLevel(int level);

    int course() const;
    void setCourse(int course);

    int scoreInit() const;
    void setScoreInit(int scoreInit);

    int scoreDiff() const;
    void setScoreDiff(int scoreDiff);

protected:
    void advance(int step);

private:
    int course_;
    int level_;
    int scoreInit_;
    int scoreDiff_;
    QRectF rect_;
    QList<Measure*> measures_;
    int currentMeasure_;
    //int playProgress_;
    QElapsedTimer playProgress_;
    bool isPlaying_;
};

#endif // NOTECHART_H

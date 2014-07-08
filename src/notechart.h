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

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void play();
    Ts::DetermineValue hitTest(Ts::TaikoState state);

    void setBoundingRect(QRectF rect);

    void reset();

    Measure* createMeasure(NoteTypeList &notes,
                           QQueue<int> &ballonHits,
                           qreal tempo,
                           int noteValuePerBeat,
                           int beatsPerBar,
                           bool isGGT,
                           int appearElapsed);
    int measureCount();

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
    QRectF rect_;               // bounding rect
    QList<Measure*> measures_;
    int currentMeasure_;        // latest display measure
    QElapsedTimer playProgress_;
    bool isPlaying_;
    int detMeasureDon_;     // determine measure index for don
    int detMeasureKa_;      // determine measure index for ka
    int detNoteDon_;        // determine note index for don
    int detNoteKa_;         // determine note index for ka
};

#endif // NOTECHART_H

#ifndef NOTECHART_H
#define NOTECHART_H

#include "measure.h"
#include "../stable.h"

#include <QElapsedTimer>
#include <QGraphicsObject>

class NoteChart : public QGraphicsObject
{
    Q_OBJECT
public:
    NoteChart(QGraphicsItem *parent = 0);

    void setBoundingRect(QRectF rect);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void play();

    void reset();

    Measure* createMeasure(NoteTypeList &notes,
                           QQueue<int> &ballonHits,
                           qreal tempo,
                           int noteValuePerBeat,
                           int beatsPerBar,
                           bool isGGT,
                           int appearElapsed);

    int measureCount() { return measures_.count(); }
    void clear();

    int level() const { return level_; }
    void setLevel(int level) { level_ = level; }

    int course() const { return course_; }
    void setCourse(int course) { course_ = course; }

    int scoreInit() const { return scoreInit_; }
    void setScoreInit(int scoreInit) { scoreInit_ = scoreInit; }

    int scoreDiff() const { return scoreDiff_; }
    void setScoreDiff(int scoreDiff) { scoreDiff_ = scoreDiff; }

protected:
    void advance(int phase);

signals:
    void determined(Ts::DetermineValue value);

public slots:
    void hit(Ts::TaikoState state);

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
    int detMeasure_;     // determine measure index
    int detNote_;        // determine note index
};

#endif // NOTECHART_H

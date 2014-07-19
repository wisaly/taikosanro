#ifndef NOTECHART_H
#define NOTECHART_H

#include <QElapsedTimer>
#include <QGraphicsObject>
#include "measure.h"
#include "score.h"
#include "../stable.h"


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

    Measure* createMeasure();

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

    Score *score() { return &score_; }

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
    Score score_;
    QRectF noteRect_;
};

#endif // NOTECHART_H

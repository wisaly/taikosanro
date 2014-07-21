#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include "../stable.h"

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(QObject *parent = 0);

    void init(Ts::Course course,int scoreInit,int scoreDiff);
    void add(Ts::DetermineValue detValue,bool isBigNote,bool isGGT);
signals:
    void scoreAdded(int delta);
    void scoreChanged(int score);
    void comboChanged(int combo);
    void consecutiveChanged(int count);
    void soulChanged(int soul);
    void qualified(bool isQualified);
public slots:

private:
    int score_;         // score value
    int scoreInit_;     // init score add value
    int scoreDiff_;     // delta score add value
    int combo_;         // combo count
    int consecutiveHit_;// consecutive hit count, include ballon and yellow bar
    int soul_;          // soul gauge value (0 ~ 10000)
    int qualifiedSoul_; // qualified soul gauge value
};

#endif // SCORE_H

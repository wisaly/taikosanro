#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include "../stable.h"

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score(QObject *parent = 0);

    void init(int scoreInit,int scoreDiff);
    void add(Ts::DetermineValue detValue,bool isBigNote,bool isGGT);
signals:
    void scoreAdded(int delta);
    void scoreChanged(int score);
    void comboChanged(int combo);
    void consecutiveChanged(int count);
public slots:

private:
    int score_;
    int scoreInit_;
    int scoreDiff_;
    int combo_;
    int consecutiveHit_;
};

#endif // SCORE_H

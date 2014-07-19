#include <QDebug>
#include "score.h"

Score::Score(QObject *parent) :
    QObject(parent),
    score_(0)
{
}

void Score::init(int scoreInit, int scoreDiff)
{
    scoreInit_ = scoreInit;
    scoreDiff_ = scoreDiff;
    score_ = 0;
    combo_ = 0;
    consecutiveHit_ = 0;
}

void Score::add(Ts::DetermineValue detValue, bool isBigNote, bool isGGT)
{
    int addValue = 0;

    if (detValue == Ts::OUTSIDE)
    {
        return;
    }
    else if (detValue == Ts::GREAT || detValue == Ts::GOOD)
    {
        combo_++;
        emit comboChanged(combo_);

        addValue = scoreInit_ + scoreDiff_ * qMax(10,(combo_ / 10));

        if (isBigNote)
            addValue *= 2;

        if (detValue == Ts::GOOD)
            addValue /= 2;
    }
    else if (detValue == Ts::FAIL || detValue == Ts::MISS)
    {
        if (combo_ != 0)
        {
            combo_ = 0;
            emit comboChanged(combo_);
        }
    }
    else if (detValue == Ts::CONSECUTIVE_HIT)
    {
        consecutiveHit_++;
        emit consecutiveChanged(consecutiveHit_);

        addValue = 300;

        if (isBigNote)
            addValue *= 2;
    }
    else if (detValue == Ts::CONSECUTIVE_OVER)
    {
        consecutiveHit_ = 0;
        emit consecutiveChanged(consecutiveHit_);

        addValue = 5000;
    }
    else if (detValue == Ts::PASS)
    {
        consecutiveHit_ = 0;
        emit consecutiveChanged(consecutiveHit_);
    }

    if (isGGT)
    {
        addValue = addValue * 12 / 10;
    }

    // make tenfold score
    addValue = addValue / 10 * 10;

    emit scoreAdded(addValue);

    score_ += addValue;

    emit scoreChanged(score_);
}

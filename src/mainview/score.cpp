#include <QDebug>
#include "score.h"

Score::Score(QObject *parent) :
    QObject(parent)
{
}

void Score::init(Ts::Course course, int scoreInit, int scoreDiff)
{
    scoreInit_ = scoreInit;
    scoreDiff_ = scoreDiff;
    score_ = 0;
    combo_ = 0;
    consecutiveHit_ = 0;
    soul_ = 0;
    switch(course)
    {
    case Ts::KANTAN:
        qualifiedSoul_ = 6000;
        break;
    case Ts::FUTSU:
        qualifiedSoul_ = 7000;
        break;
    case Ts::MUZUKASHII:
    case Ts::ONI:
    case Ts::URA:
        qualifiedSoul_ = 8000;
        break;
    }
}

void Score::add(Ts::DetermineValue detValue, bool isBigNote, bool isGGT)
{
    int addValue = 0;
    int soulAddValue = 0;

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
        {
            addValue /= 2;
            soulAddValue = 1;
        }
        else
        {
            soulAddValue = 2;
        }
    }
    else if (detValue == Ts::FAIL || detValue == Ts::MISS)
    {
        if (combo_ != 0)
        {
            combo_ = 0;
            emit comboChanged(combo_);
        }
        soulAddValue = -4;
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

    if (addValue != 0)
    {
        emit scoreAdded(addValue);

        score_ += addValue;
        emit scoreChanged(score_);
    }

    if (soulAddValue < 0)
    {
        soulAddValue = qMax(-soul_,soulAddValue);
    }
    if (soulAddValue > 0)
    {
        soulAddValue = qMin(10000 - soul_,soulAddValue);
    }
    if (soulAddValue != 0)
    {
        soul_ += soulAddValue;
        emit soulChanged(soul_);

        if (soul_ >= qualifiedSoul_ && (soul_ - soulAddValue) < qualifiedSoul_)
        {
            emit qualified(true);
        }
        else if (soul_ < qualifiedSoul_ && (soul_ - soulAddValue) >= qualifiedSoul_)
        {
            emit qualified(false);
        }
    }
}

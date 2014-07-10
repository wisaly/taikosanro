#include "determinerange.h"

DetermineRange::DetermineRange(int appearElapsed)
{
    setRange(appearElapsed);
}

Ts::DetermineValue DetermineRange::determine(int currentElapsed)
{
    if(currentElapsed > greatBegin_ && currentElapsed < greatEnd_)
    {
        return Ts::GREAT;
    }

    if(currentElapsed > goodBegin_ && currentElapsed < goodEnd_)
    {
        return Ts::GOOD;
    }

    if(currentElapsed > failBegin_ && currentElapsed < failEnd_)
    {
        return Ts::FAIL;
    }

    if (currentElapsed > failEnd_)
    {
        return Ts::MISS;
    }

    return Ts::OUTSIDE;
}

void DetermineRange::setRange(int elapsed, int goodRange, int greatRange, int failRange)
{
    greatBegin_ = elapsed - greatRange;
    greatEnd_ = elapsed + greatRange;
    goodBegin_ = elapsed - goodRange;
    goodEnd_ = elapsed + goodRange;
    failBegin_ = elapsed - failRange;
    failEnd_ = elapsed + failRange;

    appearElapsed_ = elapsed;
}

#include "determinerange.h"

DetermineRange::DetermineRange()
{
}

DetermineRange::Type DetermineRange::determine(int currentElapsed)
{
    if(currentElapsed > greatBegin || currentElapsed < greatEnd)
    {
        return Great;
    }

    if(currentElapsed > goodBegin || currentElapsed < goodEnd)
    {
        return Good;
    }

    if(currentElapsed > failBegin || currentElapsed < failEnd)
    {
        return Fail;
    }

    return Miss;
}

void DetermineRange::setRange(int elapsed, int goodRange, int greatRange, int failRange)
{
    greatBegin = elapsed - greatRange;
    greatEnd = elapsed + greatRange;
    goodBegin = elapsed - goodRange;
    goodEnd = elapsed + goodRange;
    failBegin = elapsed - failRange;
    failEnd = elapsed + failRange;

    exactElapsed = elapsed;
}

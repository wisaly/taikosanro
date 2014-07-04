#ifndef DETERMINERANGE_H
#define DETERMINERANGE_H
#include "stable.h"

class DetermineRange
{
public:

    DetermineRange(int appearElapsed_ = 0);

    Ts::DetermineValue determine(int currentElapsed);

    void setRange(int elapsed,
                  int goodRange = Ts::GOOD_RANGE,
                  int greatRange = Ts::GREAT_RANGE,
                  int failRange = Ts::FAIL_RANGE);
private:
    int greatBegin_;
    int greatEnd_;
    int goodBegin_;
    int goodEnd_;
    int failBegin_;
    int failEnd_;
    int appearElapsed_;
};

#endif // DETERMINERANGE_H

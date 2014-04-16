#ifndef DETERMINERANGE_H
#define DETERMINERANGE_H
#include <QDateTime>

class DetermineRange
{
public:
    enum Type{
        Great,
        Good,
        Fail,
        Miss
    };

    DetermineRange();

    Type determine(int currentElapsed);

    void set(int elapsed,int goodRange,int greatRange,int failRange);
private:
    int greatBegin;
    int greatEnd;
    int goodBegin;
    int goodEnd;
    int failBegin;
    int failEnd;
    int exactElapsed;
};

#endif // DETERMINERANGE_H

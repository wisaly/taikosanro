#ifndef STABLE_H
#define STABLE_H

namespace Ts
{
enum TaikoState
{
    NO_ACT = 0,
    DON_LEFT = 1,
    DON_RIGHT = 2,
    DON_BOTH = DON_LEFT | DON_RIGHT,
    KA_LEFT = 4,
    KA_RIGHT = 8,
    KA_BOTH = KA_LEFT | KA_RIGHT
};

enum DetermineValue
{
    OUTSIDE,
    GREAT,
    GOOD,
    FAIL,
    MISS
};

enum Course
{
    INVALID_COURSE = -1,
    KANTAN,
    FUTSU,
    MUZUKASHII,
    ONI,
    URA
};

const int GREAT_RANGE = 50;
const int GOOD_RANGE = 150;
const int FAIL_RANGE = 217;

const int NOTE_WIDTH = 100;
const int NOTE_HEIGHT = 100;

const int BAR_WIDTH = 100;
const int BAR_EXPAND = 400;
const int BAR_HEIGHT = 400;
const int BAR_PAD = 5;

}
#endif // STABLE_H

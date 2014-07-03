#ifndef STABLE_H
#define STABLE_H

enum TaikoState
{
    DON_LEFT = 1,
    DON_RIGHT = 2,
    DON_BOTH = DON_LEFT | DON_RIGHT,
    KA_LEFT = 4,
    KA_RIGHT = 8,
    KA_BOTH = KA_LEFT | KA_RIGHT
};

const int GREAT_RANGE = 50;
const int GOOD_RANGE = 150;
const int FAIL_RANGE = 217;

const int NOTE_WIDTH = 100;
const int NOTE_HEIGHT = 100;

#endif // STABLE_H

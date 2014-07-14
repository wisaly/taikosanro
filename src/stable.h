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

enum Crown
{
    NoCrown,
    SilverCrown,
    GoldCrown
};

const int GREAT_RANGE = 50;
const int GOOD_RANGE = 150;
const int FAIL_RANGE = 217;

const int NOTE_WIDTH = 100;
const int NOTE_HEIGHT = 100;

const int BAR_WIDTH = 100;
const int BAR_EXPAND = 400;
const int BAR_HEIGHT = 464; // 424(image height) + 30 + 5*2

const char* const GUI_FONT_NAME = "微软雅黑";

const char* const resRedMarker = "../res/redmarker.png";
const char* const resBlueMarker = "../res/bluemarker.png";
const char* const resBigRedMarker = "../res/bigredmarker.png";
const char* const resBigBlueMarker = "../res/bigbluemarker.png";

const char* const resYellowBarBody = "../res/yellowbarbody.png";
const char* const resYellowBarHead = "../res/yellowbarhead.png";
const char* const resYellowBarTail = "../res/yellowbartail.png";

const char* const resBigYellowBarBody = "../res/bigyellowbarbody.png";
const char* const resBigYellowBarHead = "../res/bigyellowbarhead.png";
const char* const resBigYellowBarTail = "../res/bigyellowbartail.png";

const char* const resSelectBarLeft = "../res/selectbarleft.png";
const char* const resSelectBarMid = "../res/selectbarmid.png";
const char* const resSelectBarRight = "../res/selectbarright.png";

const char* const resLevelStarBack = "../res/levelstarback.png";
const char* const resLevelStar = "../res/levelstar.png";

const char* const resLittleKantan = "../res/littlekantan.png";
const char* const resLittleFutsu = "../res/littlefutsu.png";
const char* const resLittleMuzukashii = "../res/littlemuzukashii.png";
const char* const resLittleOni = "../res/littleoni.png";

const char* const resCrownSilver = "../res/crownsilver.png";
const char* const resCrownGold = "../res/crowngold.png";

const char* const resSelectArrow = "../res/selectarrow.png";

}
#endif // STABLE_H

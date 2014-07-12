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

char* const GUI_FONT_NAME = "微软雅黑";

char* const resRedMarker = "../res/redmarker.png";
char* const resBlueMarker = "../res/bluemarker.png";
char* const resBigRedMarker = "../res/bigredmarker.png";
char* const resBigBlueMarker = "../res/bigbluemarker.png";

char* const resYellowBarBody = "../res/yellowbarbody.png";
char* const resYellowBarHead = "../res/yellowbarhead.png";
char* const resYellowBarTail = "../res/yellowbartail.png";

char* const resBigYellowBarBody = "../res/bigyellowbarbody.png";
char* const resBigYellowBarHead = "../res/bigyellowbarhead.png";
char* const resBigYellowBarTail = "../res/bigyellowbartail.png";

char* const resSelectBarLeft = "../res/selectbarleft.png";
char* const resSelectBarMid = "../res/selectbarmid.png";
char* const resSelectBarRight = "../res/selectbarright.png";

char* const resLevelStarBack = "../res/levelstarback.png";
char* const resLevelStar = "../res/levelstar.png";

char* const resLittleKantan = "../res/littlekantan.png";
char* const resLittleFutsu = "../res/littlefutsu.png";
char* const resLittleMuzukashii = "../res/littlemuzukashii.png";
char* const resLittleOni = "../res/littleoni.png";

char* const resCrownSilver = "../res/crownsilver.png";
char* const resCrownGold = "../res/crowngold.png";

char* const resSelectArrow = "../res/selectarrow.png";

}
#endif // STABLE_H

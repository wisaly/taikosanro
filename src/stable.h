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

const char* const RES_FILE = "../res/res.ini";

// resource of main view
namespace mv
{
const char* const RED_MARKER = "mainview/redmarker";
const char* const BLUE_MARKER = "mainview/bluemarker";
const char* const BIG_RED_MARKER = "mainview/bigredmarker";
const char* const BIG_BLUE_MARKER = "mainview/bigbluemarker";

const char* const YELLOW_BAR_BODY = "mainview/yellowbarbody";
const char* const YELLOW_BAR_HEAD = "mainview/yellowbarhead";
const char* const YELLOW_BAR_TAIL = "mainview/yellowbartail";

const char* const BIG_YELLOW_BAR_BODY = "mainview/bigyellowbarbody";
const char* const BIG_YELLOW_BAR_HEAD = "mainview/bigyellowbarhead";
const char* const BIG_YELLOW_BAR_TAIL = "mainview/bigyellowbartail";
}

// resource of select view
namespace sv
{
const char* const BAR_LEFT = "selectview/barleft";
const char* const BAR_MID = "selectview/barmid";
const char* const BAR_RIGHT = "selectview/barright";

const char* const STAR_BACK = "selectview/starback";
const char* const STAR = "selectview/star";

const char* const KANTAN = "selectview/littlekantan";
const char* const FUTSU = "selectview/littlefutsu";
const char* const MUZUKASHII = "selectview/littlemuzukashii";
const char* const ONI = "selectview/littleoni";

const char* const CROWN_SILVER = "selectview/crownsilver";
const char* const CROWN_GOLD = "selectview/crowngold";

const char* const SELECT_ARROW = "selectview/selectarrow";
}

// resource of result view
namespace rv
{
}

}
#endif // STABLE_H

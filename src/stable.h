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
    MISS,
    CONSECUTIVE_HIT,
    CONSECUTIVE_OVER,
    PASS
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

const int GREAT_RANGE = 25; // 3 frame
const int GOOD_RANGE = 75;  // 9 frame
const int FAIL_RANGE = 108; // 13 frame

const int NOTE_WIDTH = 100;
const int NOTE_HEIGHT = 100;

const char* const GUI_FONT_NAME = "微软雅黑";

const char* const RES_FILE = "../res/res.ini";

// resource of main view
namespace mv
{
const char* const CANVAS_BACK = "mainview/canvasback";
const char* const DETERMINE_CIRCLE = "mainview/determinecircle";

const char* const DETRESULT_SIZE = "mainview/detresult/size";
const char* const DETRESULT_POS1 = "mainview/detresult/pos1";
const char* const DETRESULT_POS2 = "mainview/detresult/pos2";
const char* const DETGREAT = "mainview/detgreat";
const char* const DETGOOD = "mainview/detgood";
const char* const DETFAIL = "mainview/detfail";

const char* const NOTE_POS = "mainview/note/pos";
const char* const NOTE_SIZE = "mainview/note/size";

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

const char* const STATE_BACK = "mainview/stateback";
const char* const STATE_DON_L = "mainview/statedonl";
const char* const STATE_DON_R = "mainview/statedonr";
const char* const STATE_KA_L = "mainview/statekal";
const char* const STATE_KA_R = "mainview/statekar";
}

// resource of select view
namespace sv
{
const char* const BAR_SIZE = "selectview/bar/size";
const char* const BAR_EXPAND_SIZE = "selectview/bar/expandsize";
const char* const BAR_CONTENT_POS = "selectview/barcontent/pos";
const char* const BAR_CONTENT_SIZE = "selectview/barcontent/size";
const char* const BAR_HEAD_MARGIN_SIZE = "selectview/barhead/marginsize";

const char* const BAR_LEFT = "selectview/barleft";
const char* const BAR_MID = "selectview/barmid";
const char* const BAR_RIGHT = "selectview/barright";

const char* const STAR_BACK = "selectview/starback";
const char* const STAR = "selectview/star";

const char* const KANTAN = "selectview/kantan";
const char* const FUTSU = "selectview/futsu";
const char* const MUZUKASHII = "selectview/muzukashii";
const char* const ONI = "selectview/oni";

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

#include <QPainter>
#include <QDebug>
#include "selectitem.h"
#include "../pixmapmanager.h"

const int BAR_MARGIN = 18;
const int HEAD_HEIGHT = 30;
const int BAR_PAD = 5;

const int COURSE_X = BAR_PAD + BAR_MARGIN + 10 - Ts::BAR_EXPAND / 2;
const int COURSE_Y = BAR_PAD + HEAD_HEIGHT + BAR_MARGIN + 10;

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    song_(0),
    isChoosed_(false),
    courses_(this),
    selectArrow_(this)
{
    barLeftPixmap_ = PixmapManager::get(Ts::sv::BAR_LEFT);
    barMidPixmap_ = PixmapManager::get(Ts::sv::BAR_MID);
    barRightPixmap_ = PixmapManager::get(Ts::sv::BAR_RIGHT);

    resetBoundingRect();

    setCacheMode(DeviceCoordinateCache);

    selectArrow_.hide();
}

SelectItem::~SelectItem()
{
    if (song_ != 0)
    {
        delete song_;
    }
}

void SelectItem::loadSong()
{
    if (song_ == 0)
    {
        song_ = new Song(noteFile_);
        title_ = song_->title().split("").join('\n');
        subTitle_ = song_->subtitle().split("").join('\n');

        courses_.hide();

        int index = 0;
        for (Ts::Course course = Ts::KANTAN;course <= Ts::URA;course = (Ts::Course)(course + 1))
        {
            NoteChart *chart = song_->getChart(course);
            if (chart == 0)
                continue;

            CourseItem *levelStar = new CourseItem(this);
            levelStar->setCourse(course);
            levelStar->setLevel(chart->level());
            levelStar->setPos(COURSE_X + index++ * (levelStar->boundingRect().width() + BAR_PAD),COURSE_Y);

            selectArrow_.addSelection(
                        course,
                        QPointF(levelStar->x(),COURSE_Y + levelStar->boundingRect().height()));
            courses_.addToGroup(levelStar);
        }
        //courses_.addToGroup(&selectArrow_);
    }
}

void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // delay load song info
    loadSong();

    QRectF rect = boundingRect().adjusted(BAR_PAD,BAR_PAD,0 - BAR_PAD,0 - BAR_PAD);

    // draw header
    QRectF rectHead = QRectF(rect.topLeft(),QSizeF(rect.width(),HEAD_HEIGHT));
    painter->fillRect(rectHead,backColor_);

    // draw body
    QRectF rectBody = QRectF(rectHead.bottomLeft(),QSizeF(rect.width(),rect.height() - HEAD_HEIGHT));
    painter->drawPixmap(
                rectBody.left(),rectBody.top(),
                barLeftPixmap_.width(),rectBody.height(),
                barLeftPixmap_);
    painter->drawPixmap(
                rectBody.right() - barRightPixmap_.width(),rectBody.top(),
                barRightPixmap_.width(),rectBody.height(),
                barRightPixmap_);
    painter->drawPixmap(
                rectBody.left() + barLeftPixmap_.width(),rectBody.top(),
                rectBody.width() - barLeftPixmap_.width() - barRightPixmap_.width(),rectBody.height(),
                barMidPixmap_);

    rectBody.adjust(BAR_MARGIN,BAR_MARGIN,0 - BAR_MARGIN,0 - BAR_MARGIN);

    painter->setFont(QFont(Ts::GUI_FONT_NAME,15));
    if (rect_.width() == Ts::BAR_EXPAND)
    {
        painter->setPen(foreColor_);
        painter->drawText(rectHead,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));

        painter->setPen(Qt::black);
        painter->drawText(
                    rectBody.right() - 30,rectBody.top(),30,rectBody.height(),
                    Qt::AlignHCenter,title_);
        painter->drawText(
                    rectBody.right() - 60,rectBody.top(),30,rectBody.height(),
                    Qt::AlignHCenter | Qt::AlignBottom,subTitle_);

        // show courses
        courses_.show();

    }
    else
    {
        painter->setPen(foreColor_);
        painter->drawText(rectHead,Qt::AlignCenter,QString::number(index_));

        painter->setPen(Qt::black);
        painter->drawText(rectBody,Qt::AlignCenter,title_);

        courses_.hide();
    }
}

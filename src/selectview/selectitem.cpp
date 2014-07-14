#include <QPainter>
#include <QDebug>
#include "selectitem.h"
#include "../pixmapmanager.h"

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    courses_(this),
    selectArrow_(this),
    song_(0),
    isChoosed_(false)
{
    barLeftPixmap_ = PixmapManager::get(Ts::sv::BAR_LEFT);
    barMidPixmap_ = PixmapManager::get(Ts::sv::BAR_MID);
    barRightPixmap_ = PixmapManager::get(Ts::sv::BAR_RIGHT);

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
        for (Ts::Course course = Ts::KANTAN;
             course <= Ts::URA;
             course = (Ts::Course)(course + 1))
        {
            NoteChart *chart = song_->getChart(course);
            if (chart == 0)
                continue;

            CourseItem *courseItem = new CourseItem(this);
            courseItem->setCourse(course);
            courseItem->setLevel(chart->level());
            courseItem->setPos(
                        contentRect_.left() + index++ * courseItem->boundingRect().width(),
                        contentRect_.top());

            selectArrow_.addSelection(
                        course,
                        QPointF(courseItem->boundingRect().bottomLeft()));
            courses_.addToGroup(courseItem);
        }
    }
}




void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // delay load song info
    loadSong();

    // draw header
    QRectF rectHead = rect_;
    rectHead.setBottom(barMidPixmap_.pos().y());

    painter->fillRect(rectHead,backColor_);

    // draw body
    QRectF rectBody = rect_;
    rectBody.setTop(barMidPixmap_.pos().y());

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

    painter->setFont(QFont(Ts::GUI_FONT_NAME,15));
    if (rect_.width() == barMidPixmap_.extend().height())
    {
        painter->setPen(foreColor_);
        painter->drawText(rectHead,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));

        painter->setPen(Qt::black);
        painter->drawText(
                    contentRect_.right() - 30,contentRect_.top(),30,contentRect_.height(),
                    Qt::AlignHCenter,title_);
        painter->drawText(
                    contentRect_.right() - 60,contentRect_.top(),30,contentRect_.height(),
                    Qt::AlignHCenter | Qt::AlignBottom,subTitle_);

        // show courses
        courses_.show();

    }
    else
    {
        painter->setPen(foreColor_);
        painter->drawText(rectHead,Qt::AlignCenter,QString::number(index_));

        painter->setPen(Qt::black);
        painter->drawText(contentRect_,Qt::AlignCenter,title_);

        courses_.hide();
    }
}

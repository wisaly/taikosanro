#include <QPainter>
#include <QDebug>
#include "selectitem.h"
#include "../pixmapmanager.h"

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    courses_(this),
    selectArrow_(this),
    song_(0),
    expandWidth_(0),
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
        for (int course = Ts::KANTAN;course <= Ts::URA;course++)
        {
            NoteChart *chart = song_->getChart((Ts::Course)course);
            if (chart == 0)
                continue;

            CourseItem *courseItem = new CourseItem(this);
            courseItem->setCourse((Ts::Course)course);
            courseItem->setLevel(chart->level());
            courseItem->setPos(
                        contentRect_.left() + index++ * courseItem->boundingRect().width(),
                        contentRect_.top());

            selectArrow_.addSelection((Ts::Course)course,
                        QPointF(courseItem->pos().x(),
                                courseItem->pos().y() + courseItem->boundingRect().height()));
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
    QRectF headRect(
                rect_.left() + marginSize_.width(),
                rect_.top(),
                rect_.width() - marginSize_.width() * 2,
                marginSize_.height());

    painter->fillRect(headRect,backColor_);

    // draw body
    QRectF bodyRect = rect_;
    bodyRect.setTop(marginSize_.height());

    painter->drawPixmap(
                bodyRect.left(),bodyRect.top(),
                barLeftPixmap_.width(),bodyRect.height(),
                barLeftPixmap_);
    painter->drawPixmap(
                bodyRect.right() - barRightPixmap_.width(),bodyRect.top(),
                barRightPixmap_.width(),bodyRect.height(),
                barRightPixmap_);
    painter->drawPixmap(
                bodyRect.left() + barLeftPixmap_.width(),bodyRect.top(),
                bodyRect.width() - barLeftPixmap_.width() - barRightPixmap_.width(),bodyRect.height(),
                barMidPixmap_);

    painter->setFont(QFont(Ts::GUI_FONT_NAME,15));
    if (qFuzzyCompare(rect_.width(),expandWidth_))
    {
        painter->setPen(foreColor_);
        painter->drawText(headRect,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));

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
        painter->drawText(headRect,Qt::AlignCenter,QString::number(index_));

        painter->setPen(Qt::black);
        painter->drawText(bodyRect,Qt::AlignCenter,title_);

        courses_.hide();
    }
}

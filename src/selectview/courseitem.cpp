#include <QPainter>
#include "courseitem.h"
#include "../pixmapmanager.h"

const int ICON_HEIGHT = 40;
const int CROWN_HEIGHT = 30;
const int STAR_Y = 217 + ICON_HEIGHT;
const int STAR_X = 14;
const qreal STAR_SPACE = 22.6;

CourseItem::CourseItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    setCacheMode(DeviceCoordinateCache);

    backPixmap_ = PixmapManager::get(Ts::resLevelStarBack);
    starPixmap_ = PixmapManager::get(Ts::resLevelStar);
    arrowPixmap_ = PixmapManager::get(Ts::resSelectArrow);
}

void CourseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // draw crown
    if (!crownPixmap_.isNull())
    {
        painter->drawPixmap(
                    0,0,
                    crownPixmap_);
    }
    // draw course icon
    painter->drawPixmap(
                (backPixmap_.width() - coursePixmap_.width()) / 2,
                CROWN_HEIGHT + ICON_HEIGHT - coursePixmap_.height(),
                coursePixmap_);
    // draw background
    painter->drawPixmap(0,ICON_HEIGHT + CROWN_HEIGHT,backPixmap_);

    int y = STAR_Y;
    for (int i = 0;i < level_;i ++)
    {
        painter->drawPixmap(STAR_X,y - i * STAR_SPACE,starPixmap_);
    }
}

QRectF CourseItem::boundingRect() const
{
    return QRectF(0,0,backPixmap_.width(),
                  backPixmap_.height() + CROWN_HEIGHT + ICON_HEIGHT);
}

void CourseItem::setCourse(Ts::Course course)
{
    switch (course)
    {
    case Ts::KANTAN:
        coursePixmap_ = PixmapManager::get(Ts::resLittleKantan);
        break;
    case Ts::FUTSU:
        coursePixmap_ = PixmapManager::get(Ts::resLittleFutsu);
        break;
    case Ts::MUZUKASHII:
        coursePixmap_ = PixmapManager::get(Ts::resLittleMuzukashii);
        break;
    case Ts::ONI:
    case Ts::URA:
        coursePixmap_ = PixmapManager::get(Ts::resLittleOni);
        break;
    }
}

void CourseItem::setCrown(Ts::Crown crown)
{
    switch (crown) {
    case Ts::SilverCrown:
        crownPixmap_ = PixmapManager::get(Ts::resCrownSilver);
        break;
    case Ts::GoldCrown:
        crownPixmap_ = PixmapManager::get(Ts::resCrownGold);
        break;
    }
}

#include <QPainter>
#include "courseitem.h"
#include "../pixmapmanager.h"

CourseItem::CourseItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    setCacheMode(DeviceCoordinateCache);

    backPixmap_ = PixmapManager::get(Ts::sv::STAR_BACK);
    starPixmap_ = PixmapManager::get(Ts::sv::STAR);
}

void CourseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // draw crown
    if (!crownPixmap_.isNull())
    {
        painter->drawPixmap(crownPixmap_.pos(),crownPixmap_);
    }
    // draw course icon
    painter->drawPixmap(coursePixmap_.pos(),coursePixmap_);
    // draw background
    painter->drawPixmap(backPixmap_.pos(),backPixmap_);

    for (int i = 0;i < level_;i ++)
    {
        painter->drawPixmap(
                    starPixmap_.pos().x(),
                    starPixmap_.pos().y() - i * starPixmap_.extend().height(),
                    starPixmap_);
    }
}

QRectF CourseItem::boundingRect() const
{
    return QRectF(QPointF(0,0),backPixmap_.extend());
}

void CourseItem::setCourse(Ts::Course course)
{
    switch (course)
    {
    case Ts::KANTAN:
        coursePixmap_ = PixmapManager::get(Ts::sv::KANTAN);
        break;
    case Ts::FUTSU:
        coursePixmap_ = PixmapManager::get(Ts::sv::FUTSU);
        break;
    case Ts::MUZUKASHII:
        coursePixmap_ = PixmapManager::get(Ts::sv::MUZUKASHII);
        break;
    case Ts::ONI:
    case Ts::URA:
        coursePixmap_ = PixmapManager::get(Ts::sv::ONI);
        break;
    case Ts::INVALID_COURSE:
        break;
    }
}

void CourseItem::setCrown(Ts::Crown crown)
{
    switch (crown) {
    case Ts::SilverCrown:
        crownPixmap_ = PixmapManager::get(Ts::sv::CROWN_SILVER);
        break;
    case Ts::GoldCrown:
        crownPixmap_ = PixmapManager::get(Ts::sv::CROWN_GOLD);
        break;
    case Ts::NoCrown:
        break;
    }
}

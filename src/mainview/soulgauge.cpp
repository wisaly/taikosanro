#include <QPainter>
#include <QDebug>
#include "soulgauge.h"
#include "../pixmapmanager.h"

SoulGauge::SoulGauge(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    soulUnitRect_ = QRectF(PixmapManager::getPos(Ts::mv::SOULUNIT_OFFSET),
                           PixmapManager::getSize(Ts::mv::SOULUNIT_SIZE));
}

void SoulGauge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,backPixmap_);
    if (!foreRect_.isEmpty())
        painter->drawPixmap(forePixmap_.pos(),forePixmap_,foreRect_);
}

void SoulGauge::setCourse(Ts::Course course)
{
    switch (course)
    {
    case Ts::KANTAN:
        backPixmap_ = PixmapManager::get(Ts::mv::SOUL_KANTAN_BACK);
        forePixmap_ = PixmapManager::get(Ts::mv::SOUL_KANTAN_FORE);
        break;
    case Ts::FUTSU:
        backPixmap_ = PixmapManager::get(Ts::mv::SOUL_FUTSU_BACK);
        forePixmap_ = PixmapManager::get(Ts::mv::SOUL_FUTSU_FORE);
        break;
    case Ts::MUZUKASHII:
    case Ts::ONI:
    case Ts::URA:
        backPixmap_ = PixmapManager::get(Ts::mv::SOUL_ONI_BACK);
        forePixmap_ = PixmapManager::get(Ts::mv::SOUL_ONI_FORE);
        break;
    }

    prepareGeometryChange();
    rect_ = backPixmap_.rect();
    foreRect_.setHeight(forePixmap_.height());
}

void SoulGauge::soulChanged(int soul)
{
    qreal newWidth = soul / 20 * soulUnitRect_.right();
    if (!qFuzzyCompare(newWidth,foreRect_.width()))
    {
        foreRect_.setWidth(newWidth);
        update();
    }
}

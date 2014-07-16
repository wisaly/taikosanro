#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "hitlight.h"
#include "../pixmapmanager.h"

HitLight::HitLight(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    rect_ = QRectF(QPointF(0,0),PixmapManager::getSize(Ts::mv::HITLIGHT_SIZE));
}

void HitLight::setCourse(const Ts::Course &course)
{
    course_ = course;

    QString resKey;
    switch (course_)
    {
    case Ts::KANTAN:
        resKey = Ts::mv::LIGHT_KANTAN;
        break;
    case Ts::FUTSU:
        resKey = Ts::mv::LIGHT_FUTSU;
        break;
    case Ts::MUZUKASHII:
        resKey = Ts::mv::LIGHT_MUZUKASHII;
        break;
    case Ts::ONI:
    case Ts::URA:
        resKey = Ts::mv::LIGHT_ONI;
        break;
    }

    pixmap0_ = PixmapManager::get(resKey + '0');
    pixmap1_ = PixmapManager::get(resKey + '1');
    pixmap2_ = PixmapManager::get(resKey + '2');

    update();
}

void HitLight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(pixmap0_.pos(),pixmap0_);

    if (opacity1_ != 0 && opacity2_ != 1)
    {
        painter->setOpacity(opacity1_);
        painter->drawPixmap(pixmap1_.pos(),pixmap1_);
    }
    if (opacity2_ != 0)
    {
        painter->setOpacity(opacity2_);
        painter->drawPixmap(pixmap2_.pos(),pixmap2_);
    }
}

void HitLight::determined(Ts::DetermineValue value)
{
    if (value == Ts::GREAT || value == Ts::GOOD ||
            value == Ts::CONSECUTIVE_HIT || value == Ts::CONSECUTIVE_OVER)
    {
        QParallelAnimationGroup *group = new QParallelAnimationGroup();
        QPropertyAnimation *animation1 = new QPropertyAnimation(this,"opacity1");
        animation1->setDuration(200);
        animation1->setKeyValueAt(0,0);
        animation1->setKeyValueAt(0.25,1);
        animation1->setKeyValueAt(0.75,1);
        animation1->setKeyValueAt(1,0);
        group->addAnimation(animation1);

        QPropertyAnimation *animation2 = new QPropertyAnimation(this,"opacity2");
        animation2->setDuration(200);
        animation2->setKeyValueAt(0,0);
        animation2->setKeyValueAt(0.25,0);
        animation2->setKeyValueAt(0.5,1);
        animation2->setKeyValueAt(0.75,0);
        animation2->setKeyValueAt(1,0);
        group->addAnimation(animation2);

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

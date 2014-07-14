#include <QPainter>
#include "taikoitem.h"
#include "../pixmapmanager.h"
#include "../stable.h"

TaikoItem::TaikoItem(QGraphicsItem *parent)
    :QGraphicsObject(parent),
    delayState_(Ts::NO_ACT)
{
    backPixmap_ = PixmapManager::get(Ts::mv::STATE_BACK);
    donLPixmap_ = PixmapManager::get(Ts::mv::STATE_DON_L);
    donRPixmap_ = PixmapManager::get(Ts::mv::STATE_DON_R);
    kaLPixmap_ = PixmapManager::get(Ts::mv::STATE_KA_L);
    kaRPixmap_ = PixmapManager::get(Ts::mv::STATE_KA_R);
}

void TaikoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(backPixmap_.pos(),backPixmap_);

    if (delayState_ & Ts::DON_LEFT)
        painter->drawPixmap(donLPixmap_.pos(),donLPixmap_);
    if (delayState_ & Ts::DON_RIGHT)
        painter->drawPixmap(donRPixmap_.pos(),donRPixmap_);
    if (delayState_ & Ts::KA_LEFT)
        painter->drawPixmap(kaLPixmap_.pos(),kaLPixmap_);
    if (delayState_ & Ts::KA_RIGHT)
        painter->drawPixmap(kaRPixmap_.pos(),kaRPixmap_);
}

void TaikoItem::advance(int phase)
{
    if (phase)
    {
        int state = Ts::NO_ACT;

        if ((delayState_ & Ts::DON_LEFT) && donLBegin_.elapsed() < 100)
            state |= Ts::DON_LEFT;
        if ((delayState_ & Ts::DON_RIGHT) && donRBegin_.elapsed() < 100)
            state |= Ts::DON_RIGHT;
        if ((delayState_ & Ts::KA_LEFT) && kaLBegin_.elapsed() < 100)
            state |= Ts::KA_LEFT;
        if ((delayState_ & Ts::KA_RIGHT) && kaRBegin_.elapsed() < 100)
            state |= Ts::KA_RIGHT;

        if (delayState_ != state)
        {
            delayState_ = state;
            update();
        }
    }
}

void TaikoItem::hit(Ts::TaikoState state)
{
    delayState_ |= state;

    if (state & Ts::DON_LEFT)
        donLBegin_.start();
    if (state & Ts::DON_RIGHT)
        donRBegin_.start();
    if (state & Ts::KA_LEFT)
        kaLBegin_.start();
    if (state & Ts::KA_RIGHT)
        kaRBegin_.start();

    update();
}

#include <QPainter>
#include <QDebug>
#include "pixmapnumber.h"
#include "pixmapmanager.h"

PixmapNumber::PixmapNumber(const char *resKey, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    align_(Qt::AlignCenter),
    digitLength_(0)
{
    QString key(resKey);
    for (char c = '0';c <= '9';c++)
    {
        pixmaps_.append(PixmapManager::get(key + c));
    }
}

void PixmapNumber::setNumber(int number)
{
    digits_.clear();
    digitLength_ = 0;
    do
    {
        int digit = number % 10;
        digits_.append(digit);
        number /= 10;
        digitLength_ += pixmaps_[digit].width() + pixmaps_[digit].pos().x();
    }while (number > 0);

    update();
}

void PixmapNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int x = 0;
    if (align_ == Qt::AlignRight)
    {
        x = rect_.right();
    }
    else if (align_ == Qt::AlignLeft)
    {
        x = rect_.left() + digitLength_;
    }
    else if (align_ == Qt::AlignCenter)
    {
        x = rect_.left() + rect_.width() / 2 + digitLength_ / 2;
    }

    for (int i = 0;i < digits_.count();i++)
    {
        PixmapRes &pixmap = pixmaps_[digits_[i]];

        x -= pixmap.width() + pixmap.pos().x();
        painter->drawPixmap(
                    x + pixmap.pos().x(),pixmap.pos().y(),
                    pixmap);
    }
}

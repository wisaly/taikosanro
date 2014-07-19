#include <QPainter>
#include <QDebug>
#include "pixmapnumber.h"
#include "pixmapmanager.h"

PixmapNumber::PixmapNumber(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    align_(Qt::AlignCenter),
    digitLength_(0),
    group_(0)
{
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
        digitLength_ += pixmaps_[group_][digit].width() + pixmaps_[group_][digit].pos().x();
    }while (number > 0);

    update();
}

int PixmapNumber::addPixmapGroup(const char *resKey)
{
    QList<PixmapRes> group;
    QString key(resKey);
    for (char c = '0';c <= '9';c++)
    {
        group.append(PixmapManager::get(key + c));
    }
    pixmaps_.append(group);

    return pixmaps_.count() - 1;
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
        PixmapRes &pixmap = pixmaps_[group_][digits_[i]];

        x -= pixmap.width() + pixmap.pos().x();
        painter->drawPixmap(
                    QRectF(x + pixmap.pos().x(),rect_.top() + pixmap.pos().y(),
                           pixmap.width(),rect_.height()),
                    pixmap,
                    pixmap.rect());
    }
}

void PixmapNumber::setRect(const QRectF &rect)
{
    prepareGeometryChange();
    rect_ = rect;
    update();
}

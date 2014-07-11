#include "selectitem.h"
#include <QPainter>
#include <QDebug>

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    song_(0)
{
    resetBoundingRect();

    setCacheMode(DeviceCoordinateCache);
}

SelectItem::~SelectItem()
{
    if (song_ != 0)
    {
        delete song_;
    }
}

void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // delay load song info
    if (song_ == 0)
    {
        song_ = new Song(noteFile_);
        qDebug() << "load " << song_->title();
        title_ = song_->title().split("").join('\n');
        subTitle_ = song_->subtitle().split("").join('\n');
    }

    QRectF rect = boundingRect().adjusted(5,5,-5,-5);

    painter->fillRect(rect,backColor_);

    QRectF rectHead = QRectF(rect.topLeft(),QSizeF(rect.width(),30));
    QRectF rectBody = QRectF(rectHead.bottomLeft(),QSizeF(rect.width(),rect.height() - 30));

    QPen pen = QPen(Qt::black);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(rectBody);

    painter->setPen(foreColor_);
    if (rect_.width() == Ts::BAR_EXPAND)
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));

        painter->drawText(
                    rectBody.right() - 30,rectBody.top(),30,rectBody.height(),
                    Qt::AlignHCenter,title_);
        painter->drawText(
                    rectBody.right() - 60,rectBody.top(),30,rectBody.height(),
                    Qt::AlignHCenter | Qt::AlignBottom,subTitle_);
    }
    else
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString::number(index_));
        painter->drawText(rectBody,Qt::AlignCenter,title_);
    }
}

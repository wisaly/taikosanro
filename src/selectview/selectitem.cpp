#include "selectitem.h"
#include <QPainter>
#include <QDebug>

SelectItem::SelectItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    resetBoundingRect();

    setCacheMode(DeviceCoordinateCache);

    bkground_ = Qt::white;
}



void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect().adjusted(5,5,-5,-5);

    QRectF rectHead = QRectF(rect.topLeft(),QSizeF(rect.width(),30));
    painter->fillRect(rectHead,bkground_);
    if (rect_.width() == Ts::BAR_WIDTH)
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString::number(index_));
    }
    else
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));
    }

    QRectF rectBody = QRectF(rectHead.bottomLeft(),QSizeF(rect.width(),rect.height() - 30));

    painter->fillRect(rectBody,bkground_);

    QPen pen = painter->pen();
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(rectBody);

    painter->drawText(rect,Qt::AlignCenter,titleVert_);
}

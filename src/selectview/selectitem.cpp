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

    painter->fillRect(rect,bkground_);

    QRectF rectHead = QRectF(rect.topLeft(),QSizeF(rect.width(),30));
    QRectF rectBody = QRectF(rectHead.bottomLeft(),QSizeF(rect.width(),rect.height() - 30));

    QPen pen = QPen(Qt::black);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(rectBody);

    if (rect_.width() == Ts::EXPAND_WIDTH)
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString("%1/%2").arg(index_).arg(total_));
        QRectF rectTitle(rectBody.right() - 30,rectBody.top(),30,rectBody.height());
        painter->drawText(rectTitle,Qt::AlignCenter,titleVert_);
    }
    else
    {
        painter->drawText(rectHead,Qt::AlignCenter,QString::number(index_));
        painter->drawText(rectBody,Qt::AlignCenter,titleVert_);
    }
}

#include "determineresult.h"
#include <QPainter>

DetermineResult::DetermineResult(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
}

QRectF DetermineResult::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void DetermineResult::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(QFont("华文行楷",15));
    switch (result_)
    {
    case Ts::OUTSIDE:
        break;
    case Ts::GREAT:
        painter->setPen(Qt::yellow);
        painter->drawText(boundingRect(),Qt::AlignCenter,"良");
        break;
    case Ts::GOOD:
        painter->setPen(Qt::gray);
        painter->drawText(boundingRect(),Qt::AlignCenter,"可");
        break;
    case Ts::FAIL:
        painter->setPen(Qt::black);
        painter->drawText(boundingRect(),Qt::AlignCenter,"不可");
        break;
    case Ts::MISS:
        painter->setPen(Qt::black);
        painter->drawText(boundingRect(),Qt::AlignCenter,"Miss");
        break;
    }
}

void DetermineResult::advance(int step)
{
    if (step)
    {
        if (startShow_.elapsed() > 1000)
        {
            hide();
        }
    }
}

void DetermineResult::showResult(Ts::DetermineValue result)
{
    result_ = result;
    if (result_ == Ts::OUTSIDE)
        return;

    startShow_.start();
    show();
}

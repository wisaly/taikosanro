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
        painter->drawText(boundingRect(),Qt::AlignHCenter,"良");
        break;
    case Ts::GOOD:
        painter->drawText(boundingRect(),Qt::AlignHCenter,"可");
        break;
    case Ts::FAIL:
        painter->drawText(boundingRect(),Qt::AlignHCenter,"不可");
        break;
    case Ts::MISS:
        painter->drawText(boundingRect(),Qt::AlignHCenter,"Miss");
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
    if (result_ == Ts::OUTSIDE)
        return;

    result_ = result;
    startShow_.start();
    show();
}

#include "selectcanvas.h"

#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QHash>
#include "../pixmapmanager.h"
#include "../stable.h"

SelectCanvas::SelectCanvas(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    loader_("d:/taikojiro232"),
    current_(0)
{
    setCacheMode(DeviceCoordinateCache);

    QSizeF barSize = PixmapManager::getSize(Ts::sv::BAR_SIZE);
    barRect_ = QRectF(QPointF(-barSize.width() / 2,0),barSize);

    QSizeF barExpandSize = PixmapManager::getSize(Ts::sv::BAR_EXPAND_SIZE);
    barExpandRect_ = QRectF(QPointF(-barExpandSize.width() / 2,0),barExpandSize);

    barContentRect_ = QRectF(
                PixmapManager::getPos(Ts::sv::BAR_CONTENT_POS),
                PixmapManager::getSize(Ts::sv::BAR_CONTENT_SIZE));

    barHeadMarginSize_ = PixmapManager::getSize(Ts::sv::BAR_HEAD_MARGIN_SIZE);
}

QRectF SelectCanvas::boundingRect() const
{
    return rect_;
}

void SelectCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(QFont(Ts::GUI_FONT_NAME));
    if (items_.count() > 0)
    {
        painter->drawText(rect_,Qt::AlignHCenter,items_[current_]->catagory());
    }
    else
    {
        painter->drawText(rect_,Qt::AlignCenter,"No tja file found,\ncheck your config");
    }
}

void SelectCanvas::load()
{
    QList<Catagory> catagories = loader_.load();

    int count = 0;
    foreach (Catagory catagory, catagories)
    {
        foreach (QString noteFile, catagory.files())
        {
            SelectItem *item = new SelectItem(this);
            item->setCatagory(catagory.title());
            item->setForeColor(catagory.foreColor());
            item->setBackColor(catagory.backColor());
            item->setIndex(++count);
            item->setNoteFile(noteFile);
            item->setBoundingRect(barRect_);
            item->setContentRect(barContentRect_);
            item->setExpandWidth(barExpandRect_.width());
            item->setHeadMarginSize(barHeadMarginSize_);
            item->setY(50);
            items_.append(item);
        }
    }

    foreach (SelectItem *item, items_)
    {
        item->setTotal(count);
    }
}

void SelectCanvas::move(int step)
{
    if (items_.count() == 0)
    {
        return;
    }

    // calc current index
    if (qAbs(step) == 100)
    {
        // move a catagory
        step /= 100;
        bool found = false;
        for (int i = current_;i >= 0 && i < items_.count();i+=step)
        {
            if(items_[i]->catagory() != items_[current_]->catagory())
            {
                step = i - current_;
                found = true;
                break;
            }
        }
        if (!found)
            return;
    }
    else
    {
        // out of range
        if ((current_ == 0 && step < 0) ||
                (current_ == (items_.count() - 1) && step > 0))
            return;

        // out of range but still could move
        if (current_ + step < 0)
        {
            step = current_;
        }
        else if (current_ + step >= items_.count())
        {
            step = items_.count() - 1 - current_;
        }
    }

    // calc items position
    items_[current_]->setBoundingRect(barRect_);
    update();

    QParallelAnimationGroup *groupMove = new QParallelAnimationGroup(this);

    for (int i = 0;i < items_.count();i++)
    {
        // calc item position before and after move
        int xFrom = (i - current_) * barRect_.width() + rect_.width() / 2;
        int xTo = xFrom - barRect_.width() * step;
        if (step == 0 || xTo - barRect_.width() > rect_.width() || xTo + barRect_.width() < 0)
        {
            // out of bounding rect, set pos and do not animate
            items_[i]->setX(xTo);
            continue;
        }

        // animate item
        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        animation->setStartValue(xFrom);
        animation->setEndValue(xTo);
        animation->setDuration(300);

        groupMove->addAnimation(animation);
    }


    this->connect(groupMove,SIGNAL(finished()),SLOT(moveFinished()));
    groupMove->start(QAbstractAnimation::DeleteWhenStopped);
    current_ += step;
}

void SelectCanvas::moveFinished()
{
    // update catagory info
    update();

    // scale animation
    QParallelAnimationGroup *groupScale = new QParallelAnimationGroup(this);

    // expand current item
    QPropertyAnimation *aniScale = new QPropertyAnimation(items_[current_],"boundingRect");
    aniScale->setDuration(300);
    aniScale->setEndValue(barExpandRect_);
    groupScale->addAnimation(aniScale);

    // move right items
    for (int i = current_ + 1;i < items_.count();i++)
    {
        if (items_[i]->x() > rect_.width())
            break;

        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        animation->setDuration(300);
        animation->setEndValue(
                    items_[i]->x() + (barExpandRect_.width() - barRect_.width()) / 2);
        groupScale->addAnimation(animation);
    }

    // move left items
    for (int i = current_ - 1;i >= 0;i--)
    {
        if (items_[i]->x() + barRect_.width() < 0)
            break;

        QPropertyAnimation *animation = new QPropertyAnimation(items_[i],"x");
        animation->setDuration(300);
        animation->setEndValue(
                    items_[i]->x() - (barExpandRect_.width() - barRect_.width()) / 2);
        groupScale->addAnimation(animation);
    }
    groupScale->start(QAbstractAnimation::DeleteWhenStopped);
}


void SelectCanvas::keyPressEvent(QKeyEvent *event)
{
    QHash<int,int> moveAct;
    moveAct[Qt::Key_Left] = -1;
    moveAct[Qt::Key_D] = -1;
    moveAct[Qt::Key_Right] = 1;
    moveAct[Qt::Key_K] = 1;
    moveAct[Qt::Key_Up] = -10;
    moveAct[Qt::Key_S] = -10;
    moveAct[Qt::Key_Down] = 10;
    moveAct[Qt::Key_L] = 10;
    moveAct[Qt::Key_A] = -100;
    moveAct[Qt::Key_Semicolon] = 100;
    moveAct[Qt::Key_F] = 0;
    moveAct[Qt::Key_J] = 0;
    moveAct[Qt::Key_Return] = 0;

    if (moveAct.contains(event->key()))
    {
        int step = moveAct[event->key()];

        if (items_[current_]->isChoosed())
        {
            // course select
            if (step == 0)
            {
                qDebug() << items_[current_]->song()->title() << items_[current_]->selection();
            }
            else
            {
                items_[current_]->moveSelection(step);
            }
        }
        else
        {
            // song select
            if (step == 0)
            {
                items_[current_]->setChoosed(true);
            }
            else
            {
                move(step);
            }
        }
    }
    else if (event->key() == Qt::Key_G ||
             event->key() == Qt::Key_H ||
             event->key() == Qt::Key_Escape)
    {
        // cancel select
        if (items_[current_]->isChoosed())
        {
            items_[current_]->setChoosed(false);
        }
    }
}




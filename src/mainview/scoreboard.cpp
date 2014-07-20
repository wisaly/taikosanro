#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "scoreboard.h"
#include "../pixmapmanager.h"
#include "../stable.h"

ScoreBoard::ScoreBoard(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    rect_.setSize(PixmapManager::getSize(Ts::mv::SCOREBOARD_SIZE));

    totalRect_ = QRectF(PixmapManager::getPos(Ts::mv::SCORETOTAL_OFFSET),
                        PixmapManager::getSize(Ts::mv::SCORETOTAL_SIZE));
    totalScaleRect_ = totalRect_.adjusted(0,-totalRect_.height() / 5,0,0);
    total_ = new PixmapNumber(this);
    total_->setAlign(Qt::AlignRight);
    total_->setRect(totalRect_);
    total_->addPixmapGroup(Ts::mv::SCORE);
    total_->setNumber(0);

    addRect_ = QRectF(PixmapManager::getPos(Ts::mv::SCOREADD_OFFSET),
                      PixmapManager::getSize(Ts::mv::SCOREADD_SIZE));
    add_ = new PixmapNumber(this);
    //add_->hide();
    add_->setAlign(Qt::AlignRight);
    add_->setRect(addRect_);
    add_->addPixmapGroup(Ts::mv::SCORE_ADD);
}

void ScoreBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void ScoreBoard::scoreAdded(int delta)
{
    add_->setNumber(delta);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(add_,"opacity");
    opacityAnimation->setDuration(1000);
    opacityAnimation->setKeyValueAt(0.00,0);
    opacityAnimation->setKeyValueAt(0.05,1);
    opacityAnimation->setKeyValueAt(0.95,1);
    opacityAnimation->setKeyValueAt(1.00,0);
    group->addAnimation(opacityAnimation);

    QPropertyAnimation *moveAnimation = new QPropertyAnimation(add_,"pos");
    moveAnimation->setDuration(1000);
    moveAnimation->setKeyValueAt(0.00,QPointF(-addRect_.width()/2,0));
    moveAnimation->setKeyValueAt(0.05,QPointF(0,0));
    moveAnimation->setKeyValueAt(0.85,QPointF(0,0));
    moveAnimation->setKeyValueAt(0.90,QPointF(0,-addRect_.height()/2));
    moveAnimation->setKeyValueAt(1.00,QPointF(0,addRect_.height()/2));
    group->addAnimation(moveAnimation);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void ScoreBoard::scoreChanged(int score)
{
    total_->setNumber(score);

    QPropertyAnimation *animation =  new QPropertyAnimation(total_,"rect");
    animation->setDuration(200);
    animation->setKeyValueAt(0.0,totalRect_);
    animation->setKeyValueAt(0.5,totalScaleRect_);
    animation->setKeyValueAt(1.0,totalRect_);

    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

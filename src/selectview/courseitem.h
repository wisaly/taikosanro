#ifndef LEVELSTARS_H
#define LEVELSTARS_H

#include <QGraphicsItem>
#include <QPixmap>
#include "../stable.h"

class CourseItem : public QGraphicsItem
{
public:
    CourseItem(QGraphicsItem *parent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setCourse(Ts::Course course);
    void setCrown(Ts::Crown crown);

    int level() const { return level_; }
    void setLevel(int level) { level_ = qMin(qMax(level,0),10); }

    bool isSelect() const { return isSelect_; }
    void setSelect(bool isSelect) { isSelect_ = isSelect; update();}

private:
    QPixmap backPixmap_;
    QPixmap starPixmap_;
    QPixmap coursePixmap_;
    QPixmap crownPixmap_;
    QPixmap arrowPixmap_;
    int level_;
    bool isSelect_;
};

#endif // LEVELSTARS_H

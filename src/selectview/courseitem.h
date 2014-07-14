#ifndef LEVELSTARS_H
#define LEVELSTARS_H

#include <QGraphicsItem>
#include "../pixmapres.h"
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

private:
    PixmapRes backPixmap_;
    PixmapRes starPixmap_;
    PixmapRes coursePixmap_;
    PixmapRes crownPixmap_;
    int level_;
};

#endif // LEVELSTARS_H

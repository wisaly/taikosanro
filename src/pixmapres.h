#ifndef PIXMAPRES_H
#define PIXMAPRES_H

#include <QPixmap>
#include <QPointF>

// extend pixmap with position
class PixmapRes : public QPixmap
{
public:
    PixmapRes();

    QPointF pos() const { return pos_; }
    void setPos(const QPointF &pos) { pos_ = pos; }

    QSizeF extend() const { return extend_; }
    void setExtend(const QSizeF &extend) { extend_ = extend; }

private:
    QPointF pos_;
    QSizeF extend_;
};

#endif // PIXMAPRES_H

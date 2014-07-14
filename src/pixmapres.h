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

    QSizeF strenth() const { return strenth_; }
    void setStrenth(const QSizeF &strenth) { strenth_ = strenth; }

private:
    QPointF pos_;
    QSizeF strenth_;
};

#endif // PIXMAPRES_H

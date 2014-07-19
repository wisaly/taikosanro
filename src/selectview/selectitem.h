#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QGraphicsObject>
#include <QColor>
#include <QGraphicsItemGroup>
#include "courseitem.h"
#include "selectarrow.h"
#include "../song.h"
#include "../stable.h"

class SelectItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF boundingRect READ boundingRect WRITE setBoundingRect)
public:
    explicit SelectItem(QGraphicsItem *parent = 0);
    ~SelectItem();

    QRectF boundingRect() const{return rect_;}
    void setBoundingRect(const QRectF &rect){ prepareGeometryChange(); rect_ = rect;update();}
    void setContentRect(const QRectF &contentRect) { contentRect_ = contentRect; }
    void setHeadMarginSize(const QSizeF &marginSize) { marginSize_ = marginSize; }

    void setExpandWidth(const qreal &expandWidth) { expandWidth_ = expandWidth; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int index() const{return index_;}
    void setIndex(int index) { index_ = index; }

    int total() const { return total_; }
    void setTotal(int total) { total_ = total; }

    QString catagory() const { return catagory_; }
    void setCatagory(QString catagory) { catagory_ = catagory; }

    bool isChoosed() const { return isChoosed_; }
    void setChoosed(bool isChoosed) { isChoosed_ = isChoosed; selectArrow_.setVisible(isChoosed_); }

    QColor foreColor() const { return foreColor_; }
    void setForeColor(const QColor &foreColor) { foreColor_ = foreColor; }

    QColor backColor() const { return backColor_; }
    void setBackColor(const QColor &backColor) { backColor_ = backColor; }

    void setNoteFile(QString noteFile) { noteFile_ = noteFile; }

    void loadSong();
    Song *song() { return song_; }

    void moveSelection(int step) { selectArrow_.moveSelection(step); }
    Ts::Course selection() { return selectArrow_.selection(); }

signals:

public slots:

private:
    QString title_;
    QString subTitle_;
    QString catagory_;
    QString noteFile_;
    QColor foreColor_;
    QColor backColor_;
    QRectF rect_;
    QRectF contentRect_;
    QSizeF marginSize_;
    PixmapRes barLeftPixmap_;
    PixmapRes barMidPixmap_;
    PixmapRes barRightPixmap_;
    QGraphicsItemGroup courses_;
    SelectArrow selectArrow_;
    Song *song_;
    int index_;
    int total_;
    qreal expandWidth_;
    bool isChoosed_;
    bool isExpand_;
};

#endif // SELECTITEM_H

#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QGraphicsObject>
#include <QColor>
#include <QPixmap>
#include <QGraphicsItemGroup>
#include "courseitem.h"
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
    void setBoundingRect(const QRectF &rect){rect_ = rect;update();}
    void resetBoundingRect() {setBoundingRect(QRectF(0 - Ts::BAR_WIDTH / 2,0,Ts::BAR_WIDTH,Ts::BAR_HEIGHT));}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int index() const{return index_;}
    void setIndex(int index) { index_ = index; }

    int total() const { return total_; }
    void setTotal(int total) { total_ = total; }

    QString catagory() const { return catagory_; }
    void setCatagory(QString catagory) { catagory_ = catagory; }

    bool isSelect() const { return isSelect_; }
    void setSelect(bool isSelect) { isSelect_ = isSelect; }

    QColor foreColor() const { return foreColor_; }
    void setForeColor(const QColor &foreColor) { foreColor_ = foreColor; }

    QColor backColor() const { return backColor_; }
    void setBackColor(const QColor &backColor) { backColor_ = backColor; }

    void setNoteFile(QString noteFile) { noteFile_ = noteFile; }

    void loadSong();
signals:

public slots:

private:
    QString title_;
    QString subTitle_;
    QRectF rect_;
    int index_;
    int total_;
    QColor foreColor_;
    QColor backColor_;
    QString catagory_;
    QString noteFile_;
    Song *song_;
    bool isSelect_;
    QPixmap barLeftPixmap_;
    QPixmap barMidPixmap_;
    QPixmap barRightPixmap_;
    QGraphicsItemGroup courses_;
};

#endif // SELECTITEM_H

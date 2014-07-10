#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QGraphicsObject>
#include <QColor>
#include "../stable.h"

class SelectItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF boundingRect READ boundingRect WRITE setBoundingRect)
public:
    explicit SelectItem(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const{return rect_;}
    void setBoundingRect(const QRectF &rect){rect_ = rect;update();}
    void resetBoundingRect() {setBoundingRect(QRectF(0 - Ts::BAR_WIDTH / 2,0,Ts::BAR_WIDTH,Ts::BAR_HEIGHT));}

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    QString title() const{return title_;}
    void setTitle(const QString &title){title_ = title;titleVert_ = title_.split("").join('\n');}

    int index() const{return index_;}
    void setIndex(int index) { index_ = index; }

    int total() const { return total_; }
    void setTotal(int total) { total_ = total; }

signals:

public slots:

private:
    QString title_;
    QString titleVert_;
    QString subTitle_;
    QRectF rect_;
    int index_;
    int total_;
    QColor bkground_;
};

#endif // SELECTITEM_H

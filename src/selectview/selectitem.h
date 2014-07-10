#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QGraphicsObject>

class SelectItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SelectItem(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    QString title() const{return title_;}
    void setTitle(const QString &title){title_ = title;titleVert_ = title_.split("").join('\n');}

signals:

public slots:

private:
    QString title_;
    QString titleVert_;
    QString subTitle_;
};

#endif // SELECTITEM_H

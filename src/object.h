#ifndef OBJECT_H
#define OBJECT_H

//#include <QObject>
#include <QPainter>

#include <QList>

class Object
{
public:

    explicit Object(Object *parent = 0);
    virtual ~Object();

    void appendChild(Object *child);

    void updateObject();
    void renderObject(QPainter *painter);

protected:

    virtual void onUpdate();
    virtual void onRender(QPainter *painter);

private:

    QList<Object*> childs;

};

#endif // OBJECT_H

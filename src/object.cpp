#include "object.h"

Object::Object(Object *parent)
{
    if(parent)
        parent->appendChild(this);
}

Object::~Object()
{
    for(Object* p : childs)
    {
        if(p)
            delete p;
    }
}

void Object::appendChild(Object *child)
{
    childs.append(child);
}

void Object::updateObject()
{
    onUpdate();
    for(Object* p : childs)
    {
        p->updateObject();
    }
}

void Object::renderObject(QPainter *painter)
{
    onRender(painter);
    for(Object* p : childs)
    {
        p->renderObject(painter);
    }
}

void Object::onUpdate()
{

}

void Object::onRender(QPainter *painter)
{
    Q_UNUSED(painter);
}


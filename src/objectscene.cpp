#include "objectscene.h"

ObjectScene::ObjectScene(QWidget *parent) :
    QWidget(parent),
    Object(this)
{
}

void ObjectScene::updateObjects()
{
    updateObject();
}

void ObjectScene::renderObjects()
{
    update();
}

void ObjectScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    renderObject(&painter);
}

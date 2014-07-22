#ifndef OBJECTSCENE_H
#define OBJECTSCENE_H

#include "object.h"

#include <QWidget>

class ObjectScene : public QWidget, public Object
{
    Q_OBJECT
public:

    explicit ObjectScene(QWidget *parent = 0);

public slots:

    void updateObjects();
    void renderObjects();

protected:

    void paintEvent(QPaintEvent* event);

};

#endif // OBJECTSCENE_H

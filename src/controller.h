#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "stable.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    virtual void advance() = 0;
signals:
    void hit(Ts::TaikoState state);

public slots:

protected:
    int state_;
};

#endif // CONTROLLER_H

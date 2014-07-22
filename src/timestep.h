#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <QObject>

class Timestep : public QObject
{
    Q_OBJECT
public:

    explicit Timestep(QObject *parent = 0);

    void integrate(double deltaSec);

    void setUpdateSec(double sec);

signals:

    void timeout();

private:

    double updateSec;

    double processSec;
    int tickCount;

};

#endif // TIMESTEP_H

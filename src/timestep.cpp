#include "timestep.h"

Timestep::Timestep(QObject *parent) :
    QObject(parent),
    updateSec(0.0),
    processSec(0.0),
    tickCount(0)
{

}

void Timestep::integrate(double deltaSec)
{
    if(updateSec==0.0 || deltaSec<0.0)
        return;
    processSec+=deltaSec;
    while(processSec>=updateSec)
    {
        processSec-=updateSec;
        tickCount++;
        emit timeout();
    }
}

void Timestep::setUpdateSec(double sec)
{
    updateSec=sec;
    if(updateSec<0.0)
        updateSec=0.0;
}

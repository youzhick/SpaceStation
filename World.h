#ifndef WORLD_H
#define WORLD_H

#include "YTools/YtGeometry.h"
#include <QMutex>

class World
{
public:
    World();
    ~World();

    void getState(double & wheelRad, double & wheelAng, Yt::YVector & position, double & perRad, bool & isStill);

    void nextStep(const double & dt);

    void doJump(const double & speed, const double & angle);

    void reset();

    void setWheelSpeed(const double & spd);

    void setWheelRadius(const double & r);

private:
    QMutex dataMutex;

    double wheelRadius = 25;
    double wheelSpeed = 1;
    double wheelAngle = 0;
    Yt::YVector pos;
    double personRadius = 1;
    Yt::YVector v;

    bool isStandingStill = true;
};

#endif // WORLD_H

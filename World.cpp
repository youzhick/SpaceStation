#include "World.h"
#include "YTools/Utils/YConstants.h"
#include <math.h>

using namespace Yt;
// ************************************************************************************
World::World()
{
    reset();
} // World()
// ************************************************************************************
World::~World()
{
} // ~World()
// ************************************************************************************
void World::setWheelSpeed(const double & spd) {
    dataMutex.lock();
    wheelSpeed = spd;
    dataMutex.unlock();
} // setWheelSpeed()
// ************************************************************************************
void World::setWheelRadius(const double & r) {
    dataMutex.lock();
    wheelRadius = r;
    v.set(0, 0, 0);
    pos = pos.normalize2D().mul2D(r - personRadius);
    dataMutex.unlock();
} // setWheelRadius()
// ************************************************************************************
void World::reset() {
    dataMutex.lock();
    pos.set(0, wheelRadius - personRadius, 0);
    dataMutex.unlock();
} // reset()
// ************************************************************************************
void World::getState(double & wheelRad, double & wheelAng, Yt::YVector & position, double & perRad, bool & isStill) {
    dataMutex.lock();
    wheelRad = wheelRadius;
    wheelAng = wheelAngle;
    position = pos;
    perRad = personRadius;
    isStill = isStandingStill;
    dataMutex.unlock();
} // getState()
// ************************************************************************************
void World::nextStep(const double & dt) {
    dataMutex.lock();
    double dAng = wheelSpeed*dt;
    wheelAngle += dAng;
    while (wheelAngle > PI*2)
        wheelAngle -= PI*2;
    if (isStandingStill) {
        pos = pos.rotateUnit(dAng, YVector(0, 0, 1));
    } else {
        pos = pos.add2D(v.mul(dt));
        double posMod = pos.modulus2D();
        if (posMod > wheelRadius - personRadius) {
            isStandingStill = true;
            pos.dMul((wheelRadius - personRadius)/posMod);
        } // if
    } // else

    dataMutex.unlock();
} // nextStep()
// ************************************************************************************
void World::doJump(const double & speed, const double & angle) {
    dataMutex.lock();
    if (isStandingStill) {
        double horV = wheelSpeed*(wheelRadius - personRadius);
        v = pos.rotatePi2Z().normalize2D().mul2D(horV);
        YVector jumpV = pos.normalize2D().mul2D(-speed).rotateUnit(angle, YVector(0, 0, 1));
        v = v.add2D(jumpV);
        isStandingStill = false;
    } // if
    dataMutex.unlock();
} // doJump()
// ************************************************************************************

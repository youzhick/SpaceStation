#include "LifeCycle.h"
#include <QtCore>

// ************************************************************************************
LifeCycle::LifeCycle(QObject *parent)
    : QThread      (parent)
    , _isActive    (false)
    , _isPaused    (false)
    , world        (nullptr)
{
    qDebug() << "LifeCycle constructor";
} // LifeCycle()
// ************************************************************************************
LifeCycle::~LifeCycle()
{
    qDebug() << "LifeCycle destructor";
} // ~LifeCycle()
// ************************************************************************************
void LifeCycle::setWorld(World * wrld) {
    dataMutex.lock();
    world = wrld;
    dataMutex.unlock();
} // setWorld()
// ************************************************************************************
void LifeCycle::run()
{
    qDebug() << "LifeCycle thread started";

    _isActive = true;
    static qint64 lastTimestamp = QDateTime::currentMSecsSinceEpoch();
    while (_isActive)
    {
        qint64 curTime = QDateTime::currentMSecsSinceEpoch();
        double dt = (curTime - lastTimestamp)/1000.0;
        dataMutex.lock();
        if (world) {
            world->nextStep(dt);
            emit signalWorldUpdated();
        } // if
        dataMutex.unlock();
        thread()->msleep(10);
        lastTimestamp = curTime;
    } // while

    _isActive = false;

    qDebug() << "LifeCycle thread finished";
} // run()
// ************************************************************************************

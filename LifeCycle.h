#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include <QThread>
#include <QMutex>
#include "World.h"

class LifeCycle : public QThread
{
    Q_OBJECT
public:
    LifeCycle(QObject * parent);
    ~LifeCycle();

    void run();

    inline bool isActive  () { return _isActive; }
    inline bool isPaused  () { return _isPaused; }

    inline void stop     () { _isActive = false; }
    inline void setPause (const bool & doPause) { _isPaused  = doPause; }

    void setWorld(World * wrld);

private:
    bool _isActive;
    bool _isPaused;
    QMutex dataMutex;
    World * world;

signals:
    void signalWorldUpdated();

public slots:
};

#endif // LIFECYCLE_H

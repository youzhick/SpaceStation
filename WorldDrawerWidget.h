#ifndef WORLDDRAWERWIDGET_H
#define WORLDDRAWERWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QPointF>
#include "World.h"
#include <vector>

class WorldDrawerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldDrawerWidget(QWidget *parent = nullptr);
    ~WorldDrawerWidget();
    void paintEvent(QPaintEvent *);

    void setWorld(World * wrld);

    void setStickToFloor(const bool & doStick);
    void setStickTraceToFloor(const bool & doStick);
    void setDrawTrace(const int & count);

    void clearPath();

private:
    QMutex changeMutex;

    World * world;
    QImage * bgImg;
    double innerAngle;

    // Parameters

    bool doStickToFloor = true;
    bool doStickTraceToFloor = true;

    bool doDrawTrace = true;
    int tracesCount = 1;

    QRectF fitRect2Rect(const QRectF &r1, const QRectF &r2);

    std::vector < QPointF > path1;
    std::vector < QPointF > path2;

signals:

public slots:
};

#endif // WORLDDRAWERWIDGET_H

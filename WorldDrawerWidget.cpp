#include "WorldDrawerWidget.h"
#include <QPainter>
#include <QImage>
#include <QDebug>
#include "YTools/YtGeometry.h"
#include "YTools/Utils/YConstants.h"
#include <math.h>

using namespace Yt;

WorldDrawerWidget::WorldDrawerWidget(QWidget *parent)
    : QWidget(parent)
    , world(nullptr)
    , bgImg (nullptr)
    , innerAngle (0)
{
    bgImg = new QImage("bg.jpg");
    //bgImg = new QImage("bg_smaller.jpg");
    path1.resize(0);
    path1.reserve(100);
    path2.resize(0);
    path2.reserve(100);
    qDebug() << "BG image: " << bgImg->width() << "x" << bgImg->height();
} // WorldDrawerWidget()
// *********************************************************************************************************************
WorldDrawerWidget::~WorldDrawerWidget() {
    if (bgImg)
        delete bgImg;
} // ~WorldDrawerWidget()
// *********************************************************************************************************************
void WorldDrawerWidget::setWorld(World* wrld) {
    changeMutex.lock();
    world = wrld;
    changeMutex.unlock();
} // setWorld()
// *********************************************************************************************************************
QRectF WorldDrawerWidget::fitRect2Rect(const QRectF &r1, const QRectF &r2) {
    double minR1 = r1.width() < r1.height() ? r1.width() : r1.height();
    double maxR2 = sqrt(r2.width()*r2.width() + r2.height()*r2.height());
    double scale = maxR2/minR1;
    double tarW = r1.width()*scale;
    double tarH = r1.height()*scale;
    double startX = (0 - tarW)/2;
    double startY = (0 - tarH)/2;

    return QRectF(startX, startY, tarW, tarH);
} // fitRect2Rect()
// *********************************************************************************************************************
QPointF rotate(const QPointF & p, const double & angle) {
    YVector v = YVector(p.x(), p.y(), 0).rotateUnit(angle, YVector(0, 0, 1));
    return QPointF(v.x, v.y);
} // rotate()
// *********************************************************************************************************************
void WorldDrawerWidget::paintEvent(QPaintEvent *) {
    changeMutex.lock();
    QPainter pnt (this);
    pnt.fillRect(0, 0, width(), height(), QColor(255, 255, 255, 255));
    if (world) {
        double wheelAngle(0);
        double wheelRad(0);
        double personRadius(1);
        bool isStandingStill;
        int spicCount (60);
        YVector personPos;
        world->getState(wheelRad, wheelAngle, personPos, personRadius, isStandingStill);

        double floorThickness(wheelRad*0.1);
        QRectF drawRect = fitRect2Rect(bgImg->rect(), this->rect());

        // Background
        pnt.translate(width()/2, height()/2);
        if (doStickToFloor)
            pnt.rotate(-wheelAngle*PIG);
        pnt.drawImage(drawRect, *bgImg, bgImg->rect());

        // Wheel
        QPen wheelPen (QColor(200, 200, 200), Qt::SolidLine);
        wheelPen.setWidthF(4);
        pnt.setPen(wheelPen);
        double scale = (width() < height() ? width() : height())/wheelRad/2*0.85;
        pnt.drawEllipse(-wheelRad*scale, -wheelRad*scale, wheelRad*scale*2, wheelRad*scale*2);
        pnt.drawEllipse(-(wheelRad + floorThickness)*scale, -(wheelRad + floorThickness)*scale, (wheelRad + floorThickness)*scale*2, (wheelRad + floorThickness)*scale*2);

        pnt.save();
        pnt.rotate(wheelAngle*PIG);

        pnt.save();
        double angStep = 360.0/spicCount;
        wheelPen.setWidthF(2);
        for (int i = 0; i < spicCount; ++i) {
            pnt.rotate(angStep);
            pnt.drawLine(QPointF(wheelRad*scale + 2 , 0), QPointF((wheelRad + floorThickness)*scale - 2, 0));
        }
        pnt.restore();
        pnt.restore();

        // Cosmonaut
        // First save position
        QPointF curP(personPos.x*scale, personPos.y*scale);
        if (doDrawTrace) {
            bool firstTraceBindFrag = (/*doStickToFloor ==*/ doStickTraceToFloor);
            QPointF curPRot = firstTraceBindFrag ? rotate(curP, -wheelAngle) : curP;
            if (!isStandingStill) {
                if (path1.empty())
                    path1.push_back(curPRot);
                else {
                    QPointF & lastP (path1[path1.size() - 1]);
                    double thr (3);
                    if (fabs(lastP.x() - curPRot.x()) > thr || fabs(lastP.y() - curPRot.y()) > thr)
                        path1.push_back(curPRot);
                }
            } // if

            if (tracesCount > 1) {
                QPointF curPRot = !firstTraceBindFrag ? rotate(curP, -wheelAngle) : curP;
                if (!isStandingStill) {
                    if (path2.empty())
                        path2.push_back(curPRot);
                    else {
                        QPointF & lastP (path2[path2.size() - 1]);
                        double thr (3);
                        if (fabs(lastP.x() - curPRot.x()) > thr || fabs(lastP.y() - curPRot.y()) > thr)
                            path2.push_back(curPRot);
                    }
                } // if
            } // if

            // Now draw the path
            QPen pathPen1 (QColor(50, 50, 200, 255), Qt::SolidLine);
            QPen pathPen2 (QColor(200, 50, 50, 255), Qt::SolidLine);
            pathPen1.setWidthF(3);
            pathPen2.setWidthF(3);
            for (unsigned int i = 1; i < std::max(path1.size(), path2.size()); ++i) {
                if (i < path1.size()) {
                    pnt.setPen(pathPen1);
                    if (firstTraceBindFrag)
                        pnt.drawLine(rotate(path1[i], wheelAngle), rotate(path1[i-1], wheelAngle));
                    else
                        pnt.drawLine(path1[i], path1[i-1]);
                }
                if (tracesCount > 1 && i < path2.size()) {
                    pnt.setPen(pathPen2);
                    if (!firstTraceBindFrag)
                        pnt.drawLine(rotate(path2[i], wheelAngle), rotate(path2[i-1], wheelAngle));
                    else
                        pnt.drawLine(path2[i], path2[i-1]);

                } // if
            } // for
        } // if

        QPen manPen (QColor(0, 200, 0), Qt::SolidLine);
        wheelPen.setWidthF(2);
        pnt.setPen(manPen);
        QBrush manBrush (QColor(0, 200, 0, 200));
        pnt.setBrush(manBrush);
        pnt.drawEllipse(curP, personRadius*scale, personRadius*scale);

        if (doStickToFloor)
            pnt.resetTransform();

    } // if
    changeMutex.unlock();
} // paintEvent()
// *********************************************************************************************************************
void WorldDrawerWidget::setStickToFloor(const bool & doStick) {
    changeMutex.lock();
    doStickToFloor = doStick;
    changeMutex.unlock();
} // setStickToFloor()
// *********************************************************************************************************************
void WorldDrawerWidget::setStickTraceToFloor(const bool & doStick) {
    changeMutex.lock();
    doStickTraceToFloor = doStick;
    changeMutex.unlock();
} // setStickTraceToFloor()
// *********************************************************************************************************************
void WorldDrawerWidget::clearPath() {
    changeMutex.lock();
    path1.clear();
    path2.clear();
    changeMutex.unlock();
} // clearPath()
// *********************************************************************************************************************
void WorldDrawerWidget::setDrawTrace(const int & count) {
    changeMutex.lock();
    tracesCount = count;
    doDrawTrace = count > 0;
    changeMutex.unlock();
} // setDrawTrace()
// *********************************************************************************************************************

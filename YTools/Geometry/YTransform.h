/*
*           Youzhick Tools (YTools)
*     (c) Mikhail youzhick Gribkov, 2000-2012
*             youzhick@gmail.com
*
* The YTools pack is non-commertial and free for
* use for any purposes. Just don't modify the
* pack files and keep this disclamer and copyright.
*
* The YTools pack is distributed "as is". Use it on
* your own risk and don't blame me for your computer
* explosion.
*
*/

#ifndef YT_YTRANSFORM_H
#define YT_YTRANSFORM_H

#include "YVector.h"
#include "YPoint.h"

namespace Yt
{
    class YTransform
    {

        public:
            double tramsformMatrix[4][4];

            YTransform();
            YTransform(const YVector & offsetVector);
            YTransform(double offsetX, double offsetY, double offsetZ);
            YTransform(const YVector & axis, double angle);
            YTransform(double axisX, double axisY, double axisZ, double angle);
            ~YTransform();

            YPoint apply(const YPoint & p) const;
            YVector apply(const YVector & v) const;

            void addTransform(const YTransform & t);
            void addTranslation(const YVector & v);
            void addTranslation(double x, double y, double z);
            void addScaling(double scaleX, double scaleY, double scaleZ);
            void addRotation(const YVector & axis, double angle);
            void addRotation(double x, double y, double z, double angle);
            void addProjection(double left, double right, double bottom, double top, double near, double far);
            void addSimpleProjection(double centerDist);
            void addAxesPushForward();
            void addAxesPushBack();

            void print() const;
    };
} // namespace Yt

#endif // YT_YTRANSFORM_H

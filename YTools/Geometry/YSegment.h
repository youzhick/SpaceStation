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

#ifndef YT_YSEGMENT_H
#define YT_YSEGMENT_H

#include "YVector.h"

namespace Yt
{
// *************************************************************************************
    class YSegment
    {
        public:
            YVector p1;
            YVector p2;

            YSegment();
            YSegment(const YVector & lp1, const YVector & lp2);
            ~YSegment();

            YVector center() const;
            YVector intersect2D(const YSegment & s) const;// Note: z = 0 means successful intersection; z = -65536 means that there's no intersection
            double length() const;

    };
    // *************************************************************************************
} // namespace Yt

#endif // YT_YSEGMENT_H

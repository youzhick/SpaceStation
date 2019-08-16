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

#ifndef YT_YLINE_H
#define YT_YLINE_H

#include "YVector.h"
#include "YSegment.h"

namespace Yt
{
    class YLine
    {
        public:
            YVector point;
            YVector dir;

            YLine();
            YLine(const YVector & lPoint, const YVector & lDir);
            ~YLine();

            YSegment intersect (const YLine & l1, const YLine & l2) const;
            YVector intersect2D (const YLine & l1, const YLine & l2) const;
            YVector intersect2D (const YSegment & s) const;
    };
} // namespace Yt

#endif // YT_YLINE_H

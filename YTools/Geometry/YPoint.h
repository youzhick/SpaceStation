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

#ifndef YT_YPOINT_H
#define YT_YPOINT_H

namespace Yt
{
    class YPoint
    {
        public:

            double x;
            double y;
            double z;
            double t;

            YPoint();
            YPoint(double xx, double yy, double zz);
            YPoint(double xx, double yy, double zz, double tt);
            ~YPoint();

            double centerDist() const;

            void print() const;
    };
} // namespace Yt

#endif // YT_YPOINT_H

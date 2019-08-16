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

#ifndef YT_YCONSTANTS_H
#define YT_YCONSTANTS_H

// Comment the following line to exclude QT-related components
// (YT interfaces will be unaccessible)
//#define YT_QT_CONNECT

// Comment the following line to exclude 3rd party components
// (YT interfaces will still be accessible though null-functional)
//#define YT_3RD_PARTY_CONNECT

namespace Yt
{
    const static double PI  = 3.14159265358979323846;
    const static double PIG = 180./PI;
} // namespace Yt

#endif // YT_YCONSTANTS_H

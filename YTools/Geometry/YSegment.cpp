#include "YSegment.h"

using namespace Yt;

// *************************************************************************************
YSegment::YSegment()
{}
// *************************************************************************************
YSegment::YSegment(const YVector & lp1, const YVector & lp2) :
	p1 (lp1),
	p2 (lp2)
{}
// *************************************************************************************
YVector YSegment::center () const
{
    return (p1.add(p2).mul(0.5));
}
// *************************************************************************************
double YSegment::length() const
{
    return (p1.sub(p2).modulus());
}
// *************************************************************************************
YVector YSegment::intersect2D(const YSegment & s) const
{
    YVector result;

    YVector dir1 (p2.sub2D(p1));
    YVector dir2 (s.p2.sub2D(s.p1));
    double len1 (dir1.modulus2D());
    double len2 (dir2.modulus2D());
    dir1.dMul2D(1.0/len1);
    dir2.dMul2D(1.0/len2);

    double t (dir1.x*dir2.y - dir1.y*dir2.x);
    if (t == 0)
    {
        result.z = -65536;
    }
    else
    {
        double lambda1 ( (dir2.y*(s.p1.x - p1.x) + dir2.x*(p1.y - s.p1.y)) / t);
        double lambda2 (-(dir1.x*(s.p1.y - p1.y) + dir1.y*(p1.x - s.p1.x)) / t);

        result = p1.add(dir1.mul2D(lambda1));
        if (lambda1 > len1 || lambda1 < 0 || lambda2 > len2 || lambda2 < 0)
            result.z = -65536;
        else
            result.z = 0;
    }

    return (result);
}
// *************************************************************************************
YSegment::~YSegment()
{}
// *************************************************************************************

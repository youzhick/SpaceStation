#include "YLine.h"
#include "math.h"

using namespace Yt;

// *************************************************************************************
YLine::YLine()
{}
// *************************************************************************************
YLine::YLine(const YVector & lPoint, const YVector & lDir) :
	point (lPoint),
	dir (lDir.normalize())
{}
// *************************************************************************************
YVector YLine::intersect2D (const YLine & l1, const YLine & l2) const
{
    double t = (l1.dir.y*l2.dir.x - l2.dir.y*l1.dir.x);
    if (t == 0)
	t = 0.000000000000000000000000000000000000001;
    double lambda = -(l1.dir.x*(l1.point.y - l2.point.y) + l1.dir.y*(l2.point.x - l1.point.x)) / t;
    return (l2.point.add(l2.dir.mul(lambda)));
}
// *************************************************************************************
YVector YLine::intersect2D (const YSegment & s) const
{
    YVector dir1 = s.p2.sub(s.p1).normalize();

    double t = (dir1.y*dir.x - dir.y*dir1.x);
    if (t == 0)
	t = 0.000000000000000000000000000000000000001;
    double lambda = -(dir1.x*(s.p1.y - point.y) + dir1.y*(point.x - s.p1.x)) / t;

    return (point.add(dir.mul(lambda)));
}
// *************************************************************************************
YSegment YLine::intersect (const YLine & l1, const YLine & l2) const
{
    YSegment result;

    // Just as described in the Experinent 3 documentation
    double x1 = l1.dir.x + 0.0000000000000000000000001;
    double y1 = l1.dir.y + 0.0000000000000000000000001;
    double z1 = l1.dir.z + 0.0000000000000000000000001;
    double x2 = l2.dir.x + 0.0000000000000000000000001;
    double y2 = l2.dir.y + 0.0000000000000000000000001;
    double z2 = l2.dir.z + 0.0000000000000000000000001;
    double a1 = l1.point.x + 0.0000000000000000000000001;
    double b1 = l1.point.y + 0.0000000000000000000000001;
    double c1 = l1.point.z + 0.0000000000000000000000001;
    double a2 = l2.point.x + 0.0000000000000000000000001;
    double b2 = l2.point.y + 0.0000000000000000000000001;
    double c2 = l2.point.z + 0.0000000000000000000000001;

    if (fabs(y2*z1 - y1*z2) > 0.00000000001 && fabs(y1) != 0.00000000001) {
	double A = (x2 * y1 - x1 * y2) / (y2 * z1 - y1 * z2);
	double B = ( -z1 * A - x1) / y1;
	double x3 = 1 / sqrt(A * A + B * B + 1);
	double y3 = B * x3;
	double z3 = A * x3;

	double a3 = x3 * x3 * a2 + y3 * y3 * a1 + y3 * x3 * (b2 - b1) +
	  z3 * z3 * a1 + z3 * x3 * (c2 - c1);
	double b3 = b1 + y3 * (a3 - a1) / x3;
	double c3 = c1 + z3 * (a3 - a1) / x3;

	double c4 = (c3 * y1 * z2 - b3 * z1 * z2 + b2 * z2 * z1 - c2 * y2 * z1) /
	  (z2 * y1 - y2 * z1);
	double b4 = b3 + y1 * (c4 - c3) / z1;
	double a4 = a3 + x1 * (b4 - b3) / y1;
	YVector Q (a4, b4, c4);

	YVector NL (a3 - a1, b3 - b1, c3 - c1);
	YVector P = Q.sub(NL);

	result = YSegment(P, Q);
    } else {
	double L2 = (b1*x1 + a2*y1 - a1*y1 - b2*x1) / (x1*y2 - x2*y1);
	double L1 = (a2 + L2*x2 - a1) / x1;
	YVector point1 = l1.point.add(l1.dir.normalize().mul(L1));
	YVector point2 = l2.point.add(l2.dir.normalize().mul(L2));
	result = YSegment (point1, point2);
    }

    return (result);
}
// *************************************************************************************
YLine::~YLine()
{}
// *************************************************************************************

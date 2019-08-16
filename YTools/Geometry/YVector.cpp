#include <iostream>
#include "math.h"
#include "YVector.h"

using namespace Yt;

// *************************************************************************************
YVector::YVector() :
	x (0),
	y (0),
	z (0)
{}
// *************************************************************************************
YVector::YVector(double xx, double yy, double zz) :
    x (xx),
    y (yy),
    z (zz)
{}
// *************************************************************************************
YVector::YVector(double xx, double yy) :
    x (xx),
    y (yy),
    z (0)
{}
// *************************************************************************************
YVector::YVector(const YVector & v) :
	x (v.x),
	y (v.y),
	z (v.z)
{}
// *************************************************************************************
double YVector::modulus() const
{
    return(sqrt(x*x + y*y + z*z));
}
// *************************************************************************************
double YVector::modulus2D() const
{
    return(sqrt(x*x + y*y));
}
// *************************************************************************************
YVector YVector::rotate (double angle, const YVector & axis) const
{
    double sina = sin (angle);
    double cosa = cos (angle);
    double l = axis.x;
    double m = axis.y;
    double n = axis.z;
    double k = 1.0 / (l * l + m * m + n * n);
    double sinMod = sina * axis.modulus();
    double m11 = k * (l * l + (m * m + n * n) * cosa);
    double m12 = k * (l * m * (1 - cosa) - n * sinMod);
    double m13 = k * (l * n * (1 - cosa) + m * sinMod);
    double m21 = k * (l * m * (1 - cosa) + n * sinMod);
    double m22 = k * (m * m + (l * l + n * n) * cosa);
    double m23 = k * (m * n * (1 - cosa) - l * sinMod);
    double m31 = k * (l * n * (1 - cosa) - m * sinMod);
    double m32 = k * (m * n * (1 - cosa) + l * sinMod);
    double m33 = k * (n * n + (l * l + m * m) * cosa);

    return (YVector (m11 * x + m12 * y + m13 * z, m21 * x + m22 * y + m23 * z, m31 * x + m32 * y + m33 * z));
}
// *************************************************************************************
YVector YVector::rotateUnit (double angle, const YVector & axis) const
{
    double sina = sin (angle);
    double cosa = cos (angle);
    double l = axis.x;
    double m = axis.y;
    double n = axis.z;
    double k = 1.0 / (l * l + m * m + n * n);
    double m11 = k * (l * l + (m * m + n * n) * cosa);
    double m12 = k * (l * m * (1 - cosa) - n  * sina);
    double m13 = k * (l * n * (1 - cosa) + m  * sina);
    double m21 = k * (l * m * (1 - cosa) + n  * sina);
    double m22 = k * (m * m + (l * l + n * n) * cosa);
    double m23 = k * (m * n * (1 - cosa) - l  * sina);
    double m31 = k * (l * n * (1 - cosa) - m  * sina);
    double m32 = k * (m * n * (1 - cosa) + l  * sina);
    double m33 = k * (n * n + (l * l + m * m) * cosa);

    return (YVector (m11 * x + m12 * y + m13 * z, m21 * x + m22 * y + m23 * z, m31 * x + m32 * y + m33 * z));
}
// *************************************************************************************
YVector YVector::rotatePi2Z(const bool & inPositiveDirection /* = true */)
{
    if (inPositiveDirection)
        return (YVector(-y, x, z));
    else
        return (YVector(y, -x, z));
}
// *************************************************************************************
YVector YVector::normalize() const
{
    double mod = modulus();
    return (YVector (x/mod, y/mod, z/mod));
}
// *************************************************************************************
YVector YVector::normalize2D() const
{
    double mod = modulus();
    return (YVector (x/mod, y/mod, 0));
}
// *************************************************************************************
YVector YVector::mul(double val) const
{
    return (YVector (x*val, y*val, z*val));
}
// *************************************************************************************
YVector YVector::mul2D(double val) const
{
    return (YVector (x*val, y*val));
}
// *************************************************************************************
YVector YVector::add(const YVector & v) const
{
    return (YVector (v.x + x, v.y + y, v.z + z));
}
// *************************************************************************************
YVector YVector::add2D(const YVector & v) const
{
    return (YVector (v.x + x, v.y + y));
}
// *************************************************************************************
YVector YVector::sub(const YVector & v) const
{
    return (YVector (-v.x + x, -v.y + y, -v.z + z));
}
// *************************************************************************************
YVector YVector::sub2D(const YVector & v) const
{
    return (YVector (-v.x + x, -v.y + y));
}
// *************************************************************************************
YVector YVector::matrMul(double m[3][3]) const
{
    return (
	    YVector (
		m[0][0]*x + m[0][1]*y + m[0][2]*z,
		m[1][0]*x + m[1][1]*y + m[1][2]*z,
		m[2][0]*x + m[2][1]*y + m[2][2]*z
		)
	    );
}
// *************************************************************************************
double YVector::scalMul(const YVector & v) const
{
    return (v.x*x + v.y*y + v.z*z);
}
// *************************************************************************************
double YVector::scalMul2D(const YVector & v) const
{
    return (v.x*x + v.y*y);
}
// *************************************************************************************
YVector YVector::vectMul(const YVector & v) const
{
    return (
        YVector (
            y * v.z - v.y * z,
            v.x * z - x * v.z,
            x * v.y - v.x * y
            )
        );
}
// *************************************************************************************
YVector YVector::vectMul2D(const YVector & v) const
{
    return (
        YVector (
            y * v.z - v.y * z,
            v.x * z - x * v.z,
            0
            )
        );
}
// *************************************************************************************
double YVector::angle(const YVector & v) const
{
    double t = scalMul(v)/(modulus()*v.modulus());
    if (t > 1)
        t = 1;
    if (t < -1)
        t = -1;
    return (acos(t));
}
// *************************************************************************************
double YVector::angle2D(const YVector & v) const
{
    double t = scalMul2D(v)/(modulus2D()*v.modulus2D());
    if (t > 1)
        t = 1;
    if (t < -1)
        t = -1;
    return (acos(t));
}
// *************************************************************************************
void YVector::print() const
{
    std::cout
	    << "("
	    << x << ", " << y << ", " << z
	    << ") = "
	    << modulus()
	    << std::endl
	    ;
}
// *************************************************************************************
double YVector::distTo(const YVector &v) const
{
    double dx = v.x - x;
    double dy = v.y - y;
    double dz = v.z - z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}
// *************************************************************************************
double YVector::distTo2D(const YVector &v) const
{
    double dx = v.x - x;
    double dy = v.y - y;

    return sqrt(dx*dx + dy*dy);
}
// *************************************************************************************
double YVector::distScore2D(const YVector &v) const
{
    double dx = v.x - x;
    double dy = v.y - y;

    return (dx*dx + dy*dy);
}
// *************************************************************************************
YVector::~YVector()
{}
// *************************************************************************************

// **************************** DESTRUCTIVE VERSIONS ***********************************
// *************************************************************************************
void YVector::dMul(const double &val)
{
    x *= val;
    y *= val;
    z *= val;
}
// *************************************************************************************
void YVector::dMul2D(const double &val)
{
    x *= val;
    y *= val;
}
// *************************************************************************************


// *************************************************************************************
// ******************************** STATIC MEMBERS *************************************
// *************************************************************************************
YVector YVector::vectMul(const YVector & v1, const YVector & v2)
{
    return (
	    YVector (
		    v1.y * v2.z - v2.y * v1.z,
		    v2.x * v1.z - v1.x * v2.z,
		    v1.x * v2.y - v2.x * v1.y
		    )
	    );
}
// *************************************************************************************
double YVector::angle(const YVector & v1, const YVector & v2)
{
    double t = scalMul(v1, v2)/(v1.modulus()*v2.modulus());
    if (t > 1)
		t = 1;
    if (t < -1)
		t = -1;
    return (acos(t));
}
// *************************************************************************************
double YVector::angle2D(const YVector & v1, const YVector & v2)
{
    double t = v1.scalMul2D(v2)/(v1.modulus2D()*v2.modulus2D());
    if (t > 1)
        t = 1;
    if (t < -1)
        t = -1;
    return (acos(t));
}
// *************************************************************************************
double YVector::angleScore2D(const YVector & v1, const YVector & v2)
{
    double t = v1.scalMul2D(v2)/(v1.modulus2D()*v2.modulus2D());
    return (t);
}
// *************************************************************************************
YVector YVector::sub(const YVector & v1, const YVector & v2)
{
    return (YVector (v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}
// *************************************************************************************
YVector YVector::add(const YVector & v1, const YVector & v2)
{
    return (YVector (v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}
// *************************************************************************************
double YVector::scalMul(const YVector & v1, const YVector & v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
// *************************************************************************************
void YVector::set(double xx, double yy, double zz)
{
    x = xx;
    y = yy;
    z = zz;
}
// *************************************************************************************
void YVector::set(const YVector & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}
// *************************************************************************************

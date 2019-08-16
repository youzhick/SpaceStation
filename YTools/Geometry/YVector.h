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

#ifndef YT_YVECTOR_H
#define YT_YVECTOR_H

namespace Yt
{
    class YVector
    {
        public:
            double x;
            double y;
            double z;

            YVector ();
            YVector(double xx, double yy, double zz);
            YVector(double xx, double yy);
            YVector(const YVector & v);
            ~YVector();

            void set(double xx, double yy, double zz);
            void set(const YVector & v);

            YVector rotate (double angle, const YVector & axis) const;
            YVector rotateUnit (double angle, const YVector & axis) const; // Faster version when axis.modulus() == 1;
            YVector rotatePi2Z(const bool & inPositiveDirection = true); // Rotate the vector to Pi/2 around Z axis.
            YVector normalize() const;
            YVector matrMul(double[3][3]) const;
            YVector mul(double val) const;
            YVector add(const YVector & v) const;
            YVector sub(const YVector & v) const;
            YVector vectMul(const YVector & v) const;
            double modulus() const;
            double scalMul(const YVector & v) const;
            double angle(const YVector &v) const;
            double distTo(const Yt::YVector & v) const;

            double distTo2D(const Yt::YVector & v) const;
            double distScore2D(const Yt::YVector & v) const;
            double scalMul2D(const YVector & v) const;
            YVector vectMul2D(const YVector & v) const;
            YVector add2D(const YVector & v) const;
            YVector sub2D(const YVector & v) const;
            YVector mul2D(double val) const;
            YVector normalize2D() const;
            double angle2D(const YVector &v) const;
            double modulus2D() const;

            // Destructive versions
            void dMul(const double & val);
            void dMul2D(const double & val);

            void print() const;

            static YVector add(const YVector & v1, const YVector & v2);
            static YVector sub(const YVector & v1, const YVector & v2);
            static YVector vectMul(const YVector & v1, const YVector & v2);
            static double scalMul(const YVector & v1, const YVector & v2);
            static double angle(const YVector & v1, const YVector & v2);
            static double angle2D(const YVector & v1, const YVector & v2);
            static double angleScore2D(const YVector & v1, const YVector & v2);
    };
} // namespace Yt

#endif // YT_YVECTOR_H

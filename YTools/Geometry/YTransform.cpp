#include <iostream>
#include "YTransform.h"
#include "math.h"

using namespace Yt;

// *************************************************************************************
YTransform::YTransform()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tramsformMatrix[i][j] = i != j ? 0 : 1;
}
// *************************************************************************************
YTransform::YTransform(double offsetX, double offsetY, double offsetZ)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			tramsformMatrix[i][j] = i != j ? 0 : 1;
	tramsformMatrix[0][3] = offsetX;
	tramsformMatrix[1][3] = offsetY;
	tramsformMatrix[2][3] = offsetZ;
	tramsformMatrix[3][3] = 1;
}
// *************************************************************************************
YTransform::YTransform(const YVector & offsetVector)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			tramsformMatrix[i][j] = i != j ? 0 : 1;
	tramsformMatrix[0][3] = offsetVector.x;
	tramsformMatrix[1][3] = offsetVector.y;
	tramsformMatrix[2][3] = offsetVector.z;
	tramsformMatrix[3][3] = 1;
}
// *************************************************************************************
YTransform::YTransform(double x, double y, double z, double angle)
{
	double k = x*x + y*y + z*z;
	double cosa = cos(angle);
	double sinMod = sin(angle)*sqrt(k);

	if (sinMod == 0)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				tramsformMatrix[i][j] = i != j ? 0 : 1;
	}
	else
	{
		tramsformMatrix[0][0] = (x * x + (y * y + z * z) * cosa)/k;
		tramsformMatrix[0][1] = (x * y * (1 - cosa) - z * sinMod)/k;
		tramsformMatrix[0][2] = (x * z * (1 - cosa) + y * sinMod)/k;
		tramsformMatrix[1][0] = (x * y * (1 - cosa) + z * sinMod)/k;
		tramsformMatrix[1][1] = (y * y + (x * x + z * z) * cosa)/k;
		tramsformMatrix[1][2] = (y * z * (1 - cosa) - x * sinMod)/k;
		tramsformMatrix[2][0] = (x * z * (1 - cosa) - y * sinMod)/k;
		tramsformMatrix[2][1] = (y * z * (1 - cosa) + x * sinMod)/k;
		tramsformMatrix[2][2] = (z * z + (x * x + y * y) * cosa)/k;

		for (int i = 0; i < 3; i++)
		{
			tramsformMatrix[i][3] = 0;
			tramsformMatrix[3][i] = 0;
		}
		tramsformMatrix[3][3] = 1;
	}
}
// *************************************************************************************
YTransform::YTransform(const YVector & axis, double angle)
{

	double x = axis.x;
	double y = axis.y;
	double z = axis.z;

	double k = x*x + y*y + z*z;
	double cosa = cos(angle);
	double sinMod = sin(angle)*sqrt(k);
	
	if (sinMod == 0)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				tramsformMatrix[i][j] = i != j ? 0 : 1;
	}
	else
	{
		tramsformMatrix[0][0] = (x * x + (y * y + z * z) * cosa)/k;
		tramsformMatrix[0][1] = (x * y * (1 - cosa) - z * sinMod)/k;
		tramsformMatrix[0][2] = (x * z * (1 - cosa) + y * sinMod)/k;
		tramsformMatrix[1][0] = (x * y * (1 - cosa) + z * sinMod)/k;
		tramsformMatrix[1][1] = (y * y + (x * x + z * z) * cosa)/k;
		tramsformMatrix[1][2] = (y * z * (1 - cosa) - x * sinMod)/k;
		tramsformMatrix[2][0] = (x * z * (1 - cosa) - y * sinMod)/k;
		tramsformMatrix[2][1] = (y * z * (1 - cosa) + x * sinMod)/k;
		tramsformMatrix[2][2] = (z * z + (x * x + y * y) * cosa)/k;
	
		for (int i = 0; i < 3; i++)
		{
			tramsformMatrix[i][3] = 0;
			tramsformMatrix[3][i] = 0;
		}
		tramsformMatrix[3][3] = 1;
	}
}
// *************************************************************************************
YPoint YTransform::apply(const YPoint & p) const
{
    double theOne = 1/(p.x*tramsformMatrix[3][0] + p.y*tramsformMatrix[3][1] + p.z*tramsformMatrix[3][2] + p.t*tramsformMatrix[3][3]);
    return (
	YPoint (
	    theOne*(p.x*tramsformMatrix[0][0] + p.y*tramsformMatrix[0][1] + p.z*tramsformMatrix[0][2] + p.t*tramsformMatrix[0][3]),
	    theOne*(p.x*tramsformMatrix[1][0] + p.y*tramsformMatrix[1][1] + p.z*tramsformMatrix[1][2] + p.t*tramsformMatrix[1][3]),
	    theOne*(p.x*tramsformMatrix[2][0] + p.y*tramsformMatrix[2][1] + p.z*tramsformMatrix[2][2] + p.t*tramsformMatrix[2][3]),
	    1
	    )
	);
}
// *************************************************************************************
YVector YTransform::apply(const YVector & v) const
{
	YPoint result = YPoint(v.x, v.y, v.z);
	result = apply(result);
 
	return (YVector(result.x, result.y, result.z));
}
// *************************************************************************************
void YTransform::addTransform(const YTransform & t)
{
	double result[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < 4; k++)
				result[i][j] += t.tramsformMatrix[i][k]*tramsformMatrix[k][j];
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tramsformMatrix[i][j] = result[i][j];
}
// *************************************************************************************
void YTransform::addTranslation(double x, double y, double z)
{
	addTransform(YTransform(x, y, z));
}
// *************************************************************************************
void YTransform::addTranslation(const YVector & v)
{
	addTranslation(v.x, v.y, v.z);
}
// *************************************************************************************
void YTransform::addRotation(double x, double y, double z, double angle)
{
	addTransform(YTransform(x, y, z, angle));
}
// *************************************************************************************
void YTransform::addRotation(const YVector & axis, double angle)
{
	addRotation(axis.x, axis.y, axis.z, angle);
}
// *************************************************************************************
void YTransform::addScaling(double scaleX, double scaleY, double scaleZ)
{
	YTransform t = YTransform();
	t.tramsformMatrix[0][0] = scaleX;
	t.tramsformMatrix[1][1] = scaleY;
	t.tramsformMatrix[2][2] = scaleZ;
	addTransform(t);
}
// *************************************************************************************
void YTransform::addProjection(double l, double r, double b, double t, double n, double f)
{
	YTransform tr = YTransform();
	tr.tramsformMatrix[0][0] = 2*n/(r-l);
	tr.tramsformMatrix[0][2] = (r+l)/(r-l);
	tr.tramsformMatrix[1][1] = 2*n/(t-b);
	tr.tramsformMatrix[1][2] = (t+b)/(t-b);
	tr.tramsformMatrix[2][2] = -(f+n)/(f-n);
	tr.tramsformMatrix[2][3] = -2*f*n/(f-n);
	tr.tramsformMatrix[3][2] = -1;
	addTransform(tr);
}
// *************************************************************************************
void YTransform::addSimpleProjection(double centerDist)
{
	YTransform tr = YTransform();
	//tr.tramsformMatrix[2][2] = 0;
	//tr.tramsformMatrix[3][0] = 1;
	//tr.tramsformMatrix[3][2] = -1.0/centerDist;

	tr.tramsformMatrix[2][2] = 0;
	tr.tramsformMatrix[3][3] = 0;
	tr.tramsformMatrix[3][2] = 1.0/centerDist;
	addTransform(tr);
}
// *************************************************************************************
void YTransform::addAxesPushForward()
{
	YTransform tr = YTransform();
	tr.tramsformMatrix[0][0] = 0;
	tr.tramsformMatrix[1][1] = 0;
	tr.tramsformMatrix[2][2] = 0;

	tr.tramsformMatrix[0][1] = 1;
	tr.tramsformMatrix[1][2] = 1;
	tr.tramsformMatrix[2][0] = 1;
	addTransform(tr);
}
// *************************************************************************************
void YTransform::addAxesPushBack()
{
	YTransform tr = YTransform();
	tr.tramsformMatrix[0][0] = 0;
	tr.tramsformMatrix[1][1] = 0;
	tr.tramsformMatrix[2][2] = 0;

	tr.tramsformMatrix[1][0] = 1;
	tr.tramsformMatrix[2][1] = 1;
	tr.tramsformMatrix[0][2] = 1;
	addTransform(tr);
}
// *************************************************************************************
void YTransform::print() const
{
    std::cout << "[" << std::endl;
    for (int i = 0; i < 4; i++)
    {
	std::cout << "( ";
	for (int j = 0; j < 4; j++)
	    std::cout << tramsformMatrix[i][j] << ";\t";
	std::cout << " )" << std::endl;
    }
    std::cout << "]" << std::endl;
}
// *************************************************************************************
YTransform::~YTransform()
{}
// *************************************************************************************

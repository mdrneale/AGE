#include "point.h"
#include <math.h>

using namespace Geometry;

Point::Point(float px, float py):x(px), y(py){}

Point::~Point()
{

}

float Point::Distance(const Point & p2)
{
	float a = p2.x-x;
	float b = p2.y-y;

	a *= a;
	b *= b;

	return sqrt(a + b);
}

float Point::Length()
{
	float a = x*x;
	float b = y*y;

	return sqrt(a + b);
}

Point Point::operator-(const Point & op)
{
	return Point(x - op.x, y - op.y);
}

Point Point::operator+(const Point & op)
{
	return Point(x + op.x, y + op.y);
}

Point Point::operator/(const Point & op)
{
	return Point(x / op.x, y / op.y);
}

Point Point::operator*(const Point & op)
{
	return Point(x * op.x, y * op.y);
}

Point Point::operator/(const float f)
{
	return Point(x / f, y / f);
}

Point Point::operator*(const float f)
{
	return Point(x * f, y * f);
}

float Point::Dot(const Point & p2)
{
	return x * p2.x + y * p2.y;
}

Point Point::Normalise()
{
	*this = *this/Length();
	return Point(*this);
}

Point Point::Normal()
{
	return Point(-y,x) / Length();
}

#ifndef CIRCLE
#define CIRCLE

#include "point.h"

namespace Geometry
{
	class Circle
	{
	public:
		Circle(Point point, float radius): p(point), r(radius) {};

		Point p;
		float r;	
	};
}
#endif
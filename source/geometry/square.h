#ifndef SQUARE
#define SQUARE

#include "circle.h"

namespace Geometry
{
	class Square
	{
	public:
		Square();
		~Square();

	//	void Load(std::ifstream &in);
	//	void Save(std::ofstream &out);

		void ViewSquare();
		
		bool Intersecting(const Circle &circle);

		float left;
		float right;
		float top;
		float bottom;
	};
}
#endif
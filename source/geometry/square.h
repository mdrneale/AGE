#ifndef SQUARE
#define SQUARE

#include "circle.h"

class Square
{
public:
	Square();
	~Square();

//	void Load(std::ifstream &in);
//	void Save(std::ofstream &out);

	void ViewSquare();
	
	bool Intersecting(const Circle &circle);

	int left;
	int right;
	int top;
	int bottom;
};

#endif
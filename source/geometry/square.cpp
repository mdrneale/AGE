#include "square.h"
#include <iostream>

Square::Square(){}
Square::~Square(){}

//void Square::Load(std::ifstream &in){}
//void Square::Save(std::ofstream &out){}

void Square::ViewSquare()
{
	std::cout << "left: " << left << "  right: " << right << "  top: " << top << "  bottom: " << bottom << std::endl;
}

bool Square::Intersecting(const Circle &circle)
{
	if (circle.p.x + circle.r < left)
		return false;
	if (circle.p.x - circle.r > right)
		return false;

	if (circle.p.y + circle.r < bottom)
		return false;
	if (circle.p.y - circle.r > top)
		return false;

	return true;
}

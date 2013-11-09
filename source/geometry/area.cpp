#include "area.h"
#include <iostream>
// #include "../io/hrf.h"
// #include "../io/temparray.h"

Area::Area(): sdlPoints(NULL)
{

}

Area::~Area()
{
	// for (int a=0; a < points.size(); a++)
	// {
	// 	Point* p = points[a];
	// 	delete p;
	// }
	std::vector<Point*>::iterator p;
	for ( p = points.begin(); p != points.end(); )
	{
      	p = points.erase(p);
   	}
}

//void Area::Load(MapOfStrings & attributes)
//{
	// points.clear();

	// TempArray<float> temp = TempArray<float>(attributes["area"], attributes["HRFVERSION"]);
	// for (int a = 0; a < temp.Size(); a+=2)
	// {
	// 	points.push_back( new Point(temp[a] , temp[a+1]) );
	// }
	// CalculateBoundingBox();
//}

void Area::Load(std::ifstream &in)
{

}

void Area::Save(std::ofstream &out)
{

}

void Area::ViewArea()
{
	boundingbox.ViewSquare();
}

void Area::CalculateSDLPoints()
{
	if (sdlPoints != NULL)
	{
		delete sdlPoints;
		sdlPoints = NULL;
	}
	sdlPoints = new SDL_Point[points.size()+1];
	for(int a = 0; a < points.size() + 1; a++)
	{
		sdlPoints[a].x = points[a % points.size()]->x;
		sdlPoints[a].y = points[a % points.size()]->y;
	}

}

void Area::ToSDLPoints(SDL_Point *& p, int & count, bool closed)
{
	if (sdlPoints == NULL)
	{
		CalculateSDLPoints();
	}

	count = points.size();
	if (closed)
	{
		count += 1;
	}

	p = sdlPoints;
}

void Area::CalculateBoundingBox()
{
	Point *p1 = points[0];
	int lowX, highX, lowY, highY;
	lowX = highX = p1->x;
	lowY = highY = p1->y;

	for(int a=0; a<points.size(); a++)
	{
		p1 = points[a];
		if (p1->x < lowX) 	lowX 	= p1->x;
		if (p1->x > highX) 	highX 	= p1->x; 
		if (p1->y < lowY) 	lowY 	= p1->y; 
		if (p1->y > highY) 	highY 	= p1->y; 
	}

	boundingbox.left 	= lowX;
	boundingbox.right 	= highX;

	boundingbox.top 	= highY;
	boundingbox.bottom 	= lowY;

//	boundingbox.ViewSquare();
}

bool Area::Intersecting(const Circle &circle)
{
	if (!boundingbox.Intersecting(circle))
		return false;

	//std::cout << "warning convecs objects only" << std::endl;

	Point *p1;
	Point *p2;

	for(int a=0; a<points.size(); a++)
	{
		p1 = points[a];
		p2 = points[(a+1) % points.size()];

		if (!checkpoints(*p1, *p2, circle))
			return false;
	}
	return true;
}

bool Area::checkpoints(Point & p1,Point & p2, const Circle & circle)
{
	Point norm = (p2 - p1).Normal();
	Point cirpointinp1space = ((Point)circle.p) - p1;
	float d = cirpointinp1space.Dot(norm);
	if (d-circle.r <= 0) return true;
	return false;
}

#include "area.h"
#include <iostream>
#include "window.h"
#include <sstream>
// #include "../io/hrf.h"
// #include "../io/temparray.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace Geometry;

Area::Area(): sdlPoints(NULL)
{

}

Area::~Area()
{
	DeletePoints();
}

void Area::DeletePoints()
{
	std::vector<Point*>::iterator p;
	for ( p = points.begin(); p != points.end(); )
	{
      	p = points.erase(p);
   	}	
}

bool Area::ToJson(rapidjson::Value& val, rapidjson::Document& doc)
{
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	val.AddMember("type", "area", allocator);

	rapidjson::Value valPoints(rapidjson::kArrayType);
	for (int i = 0; i < points.size(); i++)
	{
		rapidjson::Value valPoint(rapidjson::kObjectType);
		valPoint.AddMember("x", points[i]->x, allocator);
		valPoint.AddMember("y", points[i]->y, allocator);

		valPoints.PushBack(valPoint, allocator);
	}

	val.AddMember("points", valPoints, doc.GetAllocator());

	return true;
}

bool Area::FromJson(const rapidjson::Value& val)
{
	if (std::string("area").compare(val["type"].GetString())!=0)
	{
		return false;
	}

	const rapidjson::Value& valPoints = val["points"];

	std::vector<Point*> newpoints;

	for (rapidjson::SizeType i = 0; i < valPoints.Size(); i++)
	{
		float x = valPoints[i]["x"].GetDouble();
		float y = valPoints[i]["y"].GetDouble();
		newpoints.push_back(new Point(x,y));
	}
	points = newpoints;
	return true;
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
	if (points.size() == 0)
	{
		return;
	}

	if (sdlPoints != NULL)
	{
		delete sdlPoints;
		sdlPoints = NULL;
	}
	sdlPoints = new SDL_Point[points.size()+1];
	for(int a = 0; a < points.size() + 1; a++)
	{
		sdlPoints[a].x = points[a % points.size()]->x * Window::GetWindow()->GetWidth();
		sdlPoints[a].y = points[a % points.size()]->y * Window::GetWindow()->GetHeight();
	}

}

void Area::ToSDLPoints(SDL_Point *& p, int & count, bool closed)
{
	if (points.size()==0)
	{
		p=NULL;
		count=0;
		return;
	}
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
	float lowX, highX, lowY, highY;
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
//	printf("%f,%f %f,%f %f,%f \n", p1.x, p1.y, p2.x, p2.y, circle.p.x, circle.p.y );
	Point norm = (p2 - p1).Normal();
	Point cirpointinp1space = ((Point)circle.p) - p1;
//	printf("%f %f\n", cirpointinp1space.x,cirpointinp1space.y);
	float d = cirpointinp1space.Dot(norm);
//	printf("%f\n", d);
	if (d-circle.r <= 0) return true;
//	printf("out\n");
	return false;
}

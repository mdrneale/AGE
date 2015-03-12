#ifndef AREA
#define AREA

#include <vector>

#include "point.h"
#include "circle.h"
#include "square.h"
#include <SDL2/SDL.h>
#include "jsonobject.h"

namespace Geometry
{
	class Area
	{
	public:
		Area();
		~Area();

	//	void Load(MapOfStrings & attributes);
		void Load(std::ifstream & in);
		void Save(std::ofstream & out);

		virtual bool ToJson(rapidjson::Value& val, rapidjson::Document& doc);
		virtual bool FromJson(const rapidjson::Value& val);

		bool Intersecting(const Circle & circle);
		bool checkpoints(Point & p1,Point & p2, const Circle & circle);
		
		void CalculateBoundingBox();

		void ViewArea();

		void CalculateSDLPoints();
		void ToSDLPoints(SDL_Point *& points, int & count, bool closed = false);

		std::vector<Point*> points;
		Square boundingbox;

		SDL_Point * sdlPoints;
	private:
		void DeletePoints();
	};
}
#endif
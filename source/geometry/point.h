#ifndef POINT
#define POINT

class Point
{
public:
	Point(float px, float py);
	~Point();
	float Distance(const Point & p2);
	float Length();

	float Dot(const Point & p2);
	Point Normalise();
	Point Normal();

	Point operator-(const Point & op);
	Point operator+(const Point & op);
	Point operator/(const Point & op);
	Point operator*(const Point & op);

	Point operator/(const float op);
	Point operator*(const float op);

	float x;
	float y;
};
#endif
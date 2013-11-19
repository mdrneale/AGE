#ifndef MOUSE
#define MOUSE

#include "point.h"
#include "circle.h"
#include "SDL2/SDL.h"

class Mouse
{
public:
	enum MouseStates 
	{
		CLICKED,
		HELD,
		RELEASED,
		NOTTOUCHED
	};

	Mouse();
	~Mouse();

	void Update();
	Geometry::Circle Circle();

	Geometry::Point currentPosition;
	MouseStates leftClicker;
	MouseStates rightClicker;
	MouseStates middleClicker;

private:
	MouseStates UpdateStatePressed(MouseStates & state);
	MouseStates UpdateStateReleased(MouseStates & state);
	MouseStates UpdateState(MouseStates & state);

};

#endif

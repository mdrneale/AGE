#ifndef MOUSE
#define MOUSE

#include "point.h"
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

	void Update(const SDL_Event &e);

	Point currentPosition;
	MouseStates leftClicker;
	MouseStates rightClicker;
	MouseStates middleClicker;
};

#endif

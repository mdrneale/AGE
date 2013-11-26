#include "mouse.h"
#include "window.h"
#include <stdio.h>

Mouse::Mouse(): currentPosition(0,0), leftClicker(NOTTOUCHED), rightClicker(NOTTOUCHED), middleClicker(NOTTOUCHED)
{

}

Mouse::~Mouse()
{

}

Geometry::Circle Mouse::Circle()
{
	return Geometry::Circle(currentPosition,0.0f);	
}

Mouse::MouseStates Mouse::UpdateStatePressed(Mouse::MouseStates & state)
{
	switch (state)
	{
		case CLICKED:
			state = HELD;
			break;
		case NOTTOUCHED:
		case RELEASED:
			state = CLICKED;
			break;
	}
	return state;
}

Mouse::MouseStates Mouse::UpdateStateReleased(Mouse::MouseStates & state)
{
	switch (state)
	{
		case RELEASED:
			state = NOTTOUCHED;
			break;
		case CLICKED:
		case HELD:
			state = RELEASED;
			break;
	}
	return state;
}

void Mouse::Update()
{
	SDL_PumpEvents();

	int x,y;
	int buttonstate = SDL_GetMouseState( &x, &y );
	currentPosition.x = x / (float) Window::GetWindow()->GetHeight();
	currentPosition.y = y / (float) Window::GetWindow()->GetHeight();

	if (buttonstate & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		UpdateStatePressed(leftClicker);
	}
	else
	{
		UpdateStateReleased(leftClicker);
	}

	if (buttonstate & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		UpdateStatePressed(rightClicker);
	}
	else
	{
		UpdateStateReleased(rightClicker);
	}

	if (buttonstate & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		UpdateStatePressed(middleClicker);
	}
	else
	{
		UpdateStateReleased(middleClicker);
	}
}

#include "mouse.h"
#include "window.h"

Mouse::Mouse(): currentPosition(0,0), leftClicker(NOTTOUCHED), rightClicker(NOTTOUCHED), middleClicker(NOTTOUCHED)
{

}

Mouse::~Mouse()
{

}

void Mouse::Update(const SDL_Event &e)
{
	if( e.type == SDL_MOUSEMOTION)
	{
		int x,y;
		SDL_GetMouseState( &x, &y );
		currentPosition.x = x / (float) Window::GetWindow()->GetWidth();
		currentPosition.y = y / (float) Window::GetWindow()->GetHeight();
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int buttonstate = SDL_GetMouseState( NULL, NULL);

		if (buttonstate & SDL_BUTTON(1))
		{
			switch (leftClicker)
			{
				case NOTTOUCHED:
				case RELEASED:
					leftClicker = CLICKED;
					break;
				case CLICKED:
					leftClicker = HELD;
					break;
			}
		}
		else
		{
			switch (leftClicker)
			{
				case RELEASED:
					leftClicker = NOTTOUCHED;
					break;
				case CLICKED:
				case HELD:
					leftClicker = RELEASED;
					break;
			}

		}

		if (buttonstate & SDL_BUTTON(2))
		{
			switch (rightClicker)
			{
				case NOTTOUCHED:
				case RELEASED:
					rightClicker = CLICKED;
					break;
				case CLICKED:
					rightClicker = HELD;
					break;
			}
		}
		else
		{
			switch (rightClicker)
			{
				case RELEASED:
					rightClicker = NOTTOUCHED;
					break;
				case CLICKED:
				case HELD:
					rightClicker = RELEASED;
					break;
			}

		}

		if (buttonstate & SDL_BUTTON(3))
		{
			switch (middleClicker)
			{
				case NOTTOUCHED:
				case RELEASED:
					middleClicker = CLICKED;
					break;
				case CLICKED:
					middleClicker = HELD;
					break;
			}
		}
		else
		{
			switch (middleClicker)
			{
				case RELEASED:
					middleClicker = NOTTOUCHED;
					break;
				case CLICKED:
				case HELD:
					middleClicker = RELEASED;
					break;
			}

		}

	}
}

#include "timer.h"
#include "SDL2/SDL.h"

Timer::Timer()
{
	currentTick = startTick = SDL_GetTicks();
}

void Timer::Reset()
{
	startTick = SDL_GetTicks();
}

float Timer::Time()
{
	currentTick = SDL_GetTicks();
	return (currentTick - startTick) / 1000.0f;
}

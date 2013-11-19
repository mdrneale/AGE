#ifndef ENGINEWINDOW
#define ENGINEWINDOW

#include "SDL2/SDL.h"
#include "mouse.h"
#include "keyboard.h"

class Window
{
public:
	static Window * CreateWindow(const char * title, const int width, const int height);
	static Window * GetWindow();
	static void DestroyWindow();
	static bool CheckInput();
	~Window();

	bool 			WindowExists() 	{ return windowIsWorking; }
	SDL_Window * 	GetSDLWindow() 	{ return sdlWindow; }
	int 			GetWidth() 		{ return width; }
	int 			GetHeight() 	{ return height; }

	static Mouse mouse;
	static Keyboard keyboard;

private:
	Window(const char * title, const int width, const int height);
	static Window * instance;

	SDL_Window	* sdlWindow;
	int width;
	int height;
	bool windowIsWorking;
};

#endif



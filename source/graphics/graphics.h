#ifndef ENGINEGRAPHICS
#define ENGINEGRAPHICS

#include "SDL2/SDL.h"
#include "area.h"

class Graphics
{
public:
	static Graphics * 	CreateGraphics(SDL_Window	* sdlWindow);
	static Graphics * 	GetGraphics();
	static void 		DestroyGraphics();

	bool 				GraphicsExists() 	{ return GraphicsIsWorking; }
	SDL_Renderer * 		GetSDLRenderer() 	{ return sdlRednerer; }

	void 				DrawArea(Area & area, bool closed=false);
	void 				DrawLines(SDL_Point * points, int count);

	void 				Clear();
	void 				Present();

private:
	Graphics(SDL_Window	* sdlWindow);
	~Graphics();

	static Graphics * 	instance;

	SDL_Renderer * 		sdlRednerer;
	bool 				GraphicsIsWorking;
};

#endif
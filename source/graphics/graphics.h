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
	SDL_Renderer * 		GetSDLRenderer() 	{ return sdlRenderer; }

	void 				DrawArea(Geometry::Area & area, bool closed=false);
	void 				DrawLines(SDL_Point * points, int count);

	void 				Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void 				Present();

	void				SetDrawColour(float r, float g, float b, float a = 1.0f);

private:
	Graphics(SDL_Window	* sdlWindow);
	~Graphics();

	static Graphics * 	instance;

	SDL_Renderer * 		sdlRenderer;
	bool 				GraphicsIsWorking;
};

#endif
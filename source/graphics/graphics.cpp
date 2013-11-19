#include "graphics.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "font.h"

Graphics * Graphics::instance = NULL;

Graphics * Graphics::CreateGraphics(SDL_Window	* sdlWindow)
{
    if (Graphics::instance == NULL)
    {
        Graphics::instance = new Graphics(sdlWindow);
    }
    return Graphics::instance;
}

Graphics * Graphics::GetGraphics()
{
	return Graphics::instance;
}

void Graphics::DrawArea(Geometry::Area & area, bool closed)
{
	if (area.points.size() > 1)
	{
		int count=0;
		SDL_Point * points;
		area.ToSDLPoints(points, count, closed);
		DrawLines(points, count);
	}
}

void Graphics::DrawLines(SDL_Point * points, int count)
{
	SDL_RenderDrawLines(sdlRenderer, points, count);	
}


void Graphics::SetDrawColour(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(sdlRenderer, char(r*255), char(g*255), char(b*255), char(a*255));
}


void Graphics::DestroyGraphics()
{
    if (Graphics::instance != NULL)
    {
        delete Graphics::instance;
        Graphics::instance = NULL;
    }
}

void Graphics::Clear(float r, float g, float b, float a)
{
	Uint8 ro;
	Uint8 go;
	Uint8 bo;
	Uint8 ao;

	int failed = SDL_GetRenderDrawColor( sdlRenderer, &ro, &go, &bo, &ao);

	SDL_SetRenderDrawColor(sdlRenderer, char(r*255), char(g*255), char(b*255), char(a*255));
	SDL_RenderClear( sdlRenderer );
	if (!failed)
	{
		SDL_SetRenderDrawColor(sdlRenderer, ro, go, bo, ao);		
	}
}

void Graphics::Present()
{
	SDL_RenderPresent( sdlRenderer );
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer( sdlRenderer );
	sdlRenderer = NULL;
	Font::DestroyFonts();
	IMG_Quit();
	TTF_Quit();
}

Graphics::Graphics(SDL_Window	* sdlWindow)
{
	//Create renderer for window
	sdlRenderer = SDL_CreateRenderer( sdlWindow, -1, SDL_RENDERER_ACCELERATED );
	if( sdlRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		GraphicsIsWorking = false;
		return;
	}

	//Initialize renderer color
	if (SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 0 ) != 0)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		GraphicsIsWorking = false;
		return;
	}
	 //Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		GraphicsIsWorking = false;
		return;
	}

	GraphicsIsWorking = true;
}


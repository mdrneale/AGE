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

void Graphics::DrawArea(Area & area, bool closed)
{
	int count=0;
	SDL_Point * points;
	area.ToSDLPoints(points, count, closed);
	DrawLines(points, count);
}

void Graphics::DrawLines(SDL_Point * points, int count)
{
	SDL_RenderDrawLines(sdlRednerer, points, count);	
}

void Graphics::DestroyGraphics()
{
    if (Graphics::instance != NULL)
    {
        delete Graphics::instance;
        Graphics::instance = NULL;
    }
}

void Graphics::Clear()
{
	SDL_RenderClear( sdlRednerer );
}

void Graphics::Present()
{
	SDL_RenderPresent( sdlRednerer );
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer( sdlRednerer );
	sdlRednerer = NULL;
	Font::DestroyFonts();
	IMG_Quit();
	TTF_Quit();
}

Graphics::Graphics(SDL_Window	* sdlWindow)
{
	//Create renderer for window
	sdlRednerer = SDL_CreateRenderer( sdlWindow, -1, SDL_RENDERER_ACCELERATED );
	if( sdlRednerer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		GraphicsIsWorking = false;
		return;
	}

	//Initialize renderer color
	if (SDL_SetRenderDrawColor( sdlRednerer, 0, 0, 0, 0 ) != 0)
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


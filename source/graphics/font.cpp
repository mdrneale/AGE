#include "font.h"
#include "SDL2/SDL.h"
#include <SDL2_ttf/SDL_ttf.h>
#include <sstream>
#include <stdlib.h>

FontMap Font::fonts;

Font * Font::GetFont(const char * filename, int size)
{
	std::stringstream ss;
	ss << filename << "_" << size;
	std::string fontname = ss.str();

	Font * exists = fonts[fontname];

	if (!(exists == (Font*)NULL))
	{
		return exists;
	}

	TTF_Font * font = TTF_OpenFont( filename, size );
	if( font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return NULL;
	}

	Font * ret = new Font(font);
	fonts[fontname] = ret;
	return ret;
}

void Font::DestroyFonts()
{
	fonts.clear();
}

Font::Font(void * f)
{
	font = f;
}

Font::~Font()
{
	TTF_CloseFont((TTF_Font *)font);
}




#include "texture.h"
#include "SDL_image.h"
#include "graphics.h"
#include "window.h"
#include "iohelper.h"
#include <SDL_ttf.h>

Texture::Texture(): texture(NULL)
{
}

Texture::Texture(const Texture& other)
{
	texture =other.texture;
	width = other.width;
	height = other.height;
}

// Texture& Texture::operator= (const Texture& other)
// {
// 	Texture = SDL_ConvertSurface(other.texture, other.texture->format, other.texture->flags);
// 	CalculateDimentions();
//     return *this;
// }

Texture::Texture(const char * filename): texture(NULL)
{
	SetTexture(filename);
}

Texture::Texture(SDL_Surface * t): texture(NULL)
{
	SetTexture(t);
}

Texture::Texture(Font * f, const char * text, char r, char g, char b, char a): texture(NULL)
{
	SetTexture(f,text, r, g, b, a);
}

Texture::~Texture()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture( texture );
	}
}

void Texture::SetTexture(Font * f, const char * text, char r, char g, char b, char a)
{

	SDL_Color textColor = { r, g, b, a };
	std::vector<std::string> lines = Split(text, '\n');
	int w, h = 0;
	int fw, fh = 0;

	for (int a=0; a < lines.size(); a++)
	{
		if (!TTF_SizeText((TTF_Font *)f->font, lines[a].c_str(), &w, &h))
		{
			if (w > fw)
			{
				fw = w;
			}
			fh += h;
		}
	}

	SDL_Surface* endsurface = SDL_CreateRGBSurface(	0,
                                  					fw,
                                  					fh,
                                  					32,
                                  					0,
                                  					0,
                                  					0,
                                  					0);
	fh=0;
	for (int a = 0; a < lines.size(); a++)
	{
		SDL_Surface* temptext = TTF_RenderText_Blended( (TTF_Font *)f->font, lines[a].c_str(), textColor );
		if (!TTF_SizeText((TTF_Font *)f->font, lines[a].c_str(), &w, &h))
		{
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w = w;
			src.h = h;
			SDL_Rect dst;
			dst.x = 0;
			dst.y = fh;
			dst.w = w;
			dst.h = h;
			fh += h;
			SDL_BlitSurface(temptext,
	                    	&src,
	                    	endsurface,
		                    &dst);
		}
		SDL_FreeSurface(temptext);

	}
	SetTexture(endsurface);
	SDL_FreeSurface(endsurface);
	return;
}

void Texture::SetTexture(const char * filename)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load( filename );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
		return;
	}
	else
	{
		// //Convert surface to screen format
		// optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
		// if( optimizedSurface == NULL )
		// {
		// 	printf( "Unable to optimize image %s! SDL Error: %s\n", filename, SDL_GetError() );
	 //    	return -1;
		// }

		// //Get rid of old loaded surface
		// SDL_FreeSurface( loadedSurface );
	}
	SetTexture(loadedSurface);
	SDL_FreeSurface(loadedSurface);
}

void Texture::SetTexture(SDL_Surface * t)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width 	= 0;
		height 	= 0;
	}

	texture = SDL_CreateTextureFromSurface(Graphics::GetGraphics()->GetSDLRenderer(), t);
	if (texture != NULL)
	{
		width 	= t->w;
		height 	= t->h;
	}
}

void Texture::RenderTexture(float x, float y, float w, float h, float rot)
{
	SDL_Rect dstRect;
	dstRect.x = (int) (x * Window::GetWindow()->GetWidth());
	dstRect.y = (int) (y * Window::GetWindow()->GetHeight());
	dstRect.w = (int) (w * width);
	dstRect.h = (int) (h * height);

	if (SDL_RenderCopyEx( Graphics::GetGraphics()->GetSDLRenderer(), texture, NULL, &dstRect, rot, NULL, SDL_FLIP_NONE ) != 0)
	{
		printf("Render Copy error: %s\n", SDL_GetError());
	}
}

void Texture::RenderTextureToTexture(Texture & dstTexture, float x, float y)
{
	SDL_Rect dstRect;
	dstRect.x = (int) (x * dstTexture.width);
	dstRect.y = (int) (y * dstTexture.height);
	dstRect.w = (int) dstTexture.width;
	dstRect.h = (int) dstTexture.height;

	SDL_RenderCopyEx( Graphics::GetGraphics()->GetSDLRenderer(), dstTexture.texture, NULL, &dstRect, 0, NULL, SDL_FLIP_NONE );
}

void Texture::SetBlendMode(BlendMode mode)
{
	SDL_SetTextureBlendMode(texture, (SDL_BlendMode)mode);
}

void Texture::CalculateDimentions()
{
}

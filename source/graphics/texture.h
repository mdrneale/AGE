#ifndef TEXTURE
#define TEXTURE

#include "SDL2/SDL.h"
#include "font.h"

class Texture
{
public:
    enum BlendMode 
    {
        ADD   = SDL_BLENDMODE_ADD,
        ALPHA = SDL_BLENDMODE_BLEND
    };

    Texture();
    // Texture(const Texture& other);
    Texture(Font * f, const char * text, char r, char g, char b, char a);
    Texture(SDL_Surface * texture);
	virtual ~Texture();

    void SetTexture(const char * filename);
    void SetTexture(SDL_Surface * texture);
    void SetTexture(Font * f, const char * text, char r, char g, char b, char a);

    void RenderTexture(float x=0, float y=0, float w=1.0f, float h=1.0f, float rot=0.0f, float sx=0, float sy=0, float sw=1.0f, float sh=1.0f, bool flip = false);
	void RenderTextureToTexture(Texture & dstTexture, float x=0, float y=0);

    void SetBlendMode(BlendMode mode);

    SDL_Texture	* texture;
    int width;
    int height;

private:
    void CalculateDimentions();

};

#endif
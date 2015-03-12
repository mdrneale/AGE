#include "music.h"
#include <SDL2_mixer/SDL_mixer.h>

Music::Music(): music(NULL)
{

}

Music::Music(const Music& other)
{
//	music
}

Music::Music(const char * filename)
{
	music = Mix_LoadMUS( filename );
	if( music == NULL )
	{
		printf( "Failed to load Music: %s. SDL_mixer Error: %s\n", filename, Mix_GetError() );
	}
}

void Music::Play(float volume, float fadetime)
{
	if( Mix_PlayingMusic() == 0 )
	{
		fadetime *= 0.5f;
		Mix_FadeOutMusic((int) ( fadetime * 1000));
	}
	Mix_FadeInMusic( (Mix_Music *)music, -1, (int) ( fadetime * 1000) );
	Mix_VolumeMusic( (int) (MIX_MAX_VOLUME * volume));
}

void Music::Stop(float fadetime)
{
	Mix_FadeOutMusic((int) ( fadetime * 1000));	
}

Music::~Music()
{
	if (music != NULL)
	{
		Mix_FreeMusic( (Mix_Music *)music );
		music = NULL; // unnecessary
	}
}

#include "sound.h"
#include <SDL2_mixer/SDL_mixer.h>

Sound::Sound(): soundChunk(NULL)
{

}

Sound::Sound(const Sound& other)
{
//	soundChunk
}

Sound::Sound(const char * filename)
{
	soundChunk = Mix_LoadWAV( filename );
	if( soundChunk == NULL )
	{
		printf( "Failed to load sound: %s. SDL_mixer Error: %s\n", filename, Mix_GetError() );
	}
}

void Sound::Play(float volume)
{
	channel = Mix_PlayChannel(-1, (Mix_Chunk *)soundChunk, 0);
	Mix_Volume(channel, (int) (MIX_MAX_VOLUME * volume));
}

void Sound::Stop(float fadetime)
{
	Mix_FadeOutChannel(channel, (int) ( fadetime * 1000));
}

void Sound::StopAll(float fadetime)
{
	Mix_FadeOutChannel(-1, (int) ( fadetime * 1000));
}

Sound::~Sound()
{
	if (soundChunk != NULL)
	{
		Mix_FreeChunk( (Mix_Chunk *)soundChunk );
		soundChunk = NULL; // unnecessary
	}
}

#include "audio.h"
#include <SDL_mixer.h>

Audio * Audio::instance = NULL;

Audio * Audio::CreateAudio()
{
    if (Audio::instance == NULL)
    {
        Audio::instance = new Audio();
    }
    return Audio::instance;
}

Audio * Audio::GetAudio()
{
	return Audio::instance;
}

void Audio::DestroyAudio()
{
    if (Audio::instance != NULL)
    {
        delete Audio::instance;
        Audio::instance = NULL;
    }
}

Audio::Audio()
{
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		AudioIsWorking = false;
		return;
	}
	AudioIsWorking = true;
}

Audio::~Audio()
{
	Mix_Quit();
}


#ifndef ENGINEAUDIO
#define ENGINEAUDIO

//#include "SDL.h"

class Audio
{
public:
	static Audio *		CreateAudio();
	static Audio *		GetAudio();
	static void			DestroyAudio();

	bool				AudioExists() 		{ return AudioIsWorking; }

private:
	Audio();
	~Audio();

	static Audio * 	instance;

	bool 				AudioIsWorking;
};

#endif
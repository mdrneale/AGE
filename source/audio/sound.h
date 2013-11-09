#ifndef SOUND
#define SOUND

class Sound
{
public:

    Sound();
    Sound(const Sound& other);
    Sound(const char * filename);
	~Sound();

    void Play(float volume=1.0f);
    void Stop(float fadetime=0.0f);
    static void StopAll(float fadetime=0.0f);

    int channel;
    void * soundChunk;
};

#endif
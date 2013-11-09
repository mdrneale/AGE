#ifndef MUSIC
#define MUSIC

class Music
{
public:

    Music();
    Music(const Music& other);
    Music(const char * filename);
	~Music();

    void Play(float volume = 1.0f, float fadetime = 0.0f);
    static void Stop(float fadetime=0.0f);

	void * music;
};

#endif


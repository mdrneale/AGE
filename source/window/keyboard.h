#ifndef KEYBOARD
#define KEYBOARD

#include "SDL2/SDL.h"

class Keyboard
{
public:
	enum keyStates 
	{
		DOWN,
		HELD,
		UP,
		NOTTOUCHED
	};

	Keyboard();
	~Keyboard();

	void Update();
    void KeyDown(int keyid);
	void KeyUp(int keyid);

	static const int keyCount = 323;
	keyStates keys[keyCount];
};

#endif

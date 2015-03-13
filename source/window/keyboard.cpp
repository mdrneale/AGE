#include "keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < keyCount; ++i)
	{
		keys[i] = NOTTOUCHED;
	}
}

Keyboard::~Keyboard()
{

}

void Keyboard::Update()
{
	for (int i = 0; i < keyCount; ++i)
	{
		switch (keys[i])
		{
			case DOWN:
				keys[i] = HELD;
				break;
			case UP:
				keys[i] = NOTTOUCHED;
		}
	}
}

void Keyboard::KeyDown(int keyid)
{
	keyid = NormaliseKeyID(keyid);
	if (keyid < 0 || keyid >= keyCount)
	{
		printf("Unknown key press! %i\n", keyid);
		return;
	}
	switch (keys[keyid])
	{
		case NOTTOUCHED:
		case UP:
			keys[keyid] = DOWN;
			break;
	}
}

void Keyboard::KeyUp(int keyid)
{
	keyid = NormaliseKeyID(keyid);
	if (keyid < 0 || keyid >= keyCount)
	{
		printf("Unknown key press! %i\n", keyid);
		return;
	}

	switch (keys[keyid])
	{
		case DOWN:
		case HELD:
			keys[keyid] = UP;
			break;
	}
}

int Keyboard::NormaliseKeyID(int keyid)
{
	if (keyid < 0 || keyid >= keyCount)
	{
		keyid = keyid + (keyCount-1) - SDLK_UP;
	}
	return keyid;
}

#ifndef TIMER
#define TIMER

class Timer
{
public:
	Timer();

	void Reset();
	float Time();

	int startTick;
	int currentTick;
};

#endif
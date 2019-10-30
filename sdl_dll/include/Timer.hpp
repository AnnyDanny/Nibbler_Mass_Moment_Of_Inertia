#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <SDL2/SDL.h>

//**************************************************************************************************
//	Timer
//--------------------------------------------------------------------------------------------------
class Timer
{
public:
	static Timer*	Instance();
	static void		Release();

	void			Reset();
	float			getDeltaTime();

	void			Update();

private:
	Timer();
	~Timer();

	static Timer*	sInstance;
	unsigned int	mStartTicks;
	unsigned int	mElapseTicks;
	float			mDeltaTime;
	float			mTimeScale;


};

#endif
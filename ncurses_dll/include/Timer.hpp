#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <chrono>

//**************************************************************************************************
//	Timer
//--------------------------------------------------------------------------------------------------
class Timer
{
public:
	Timer();
	~Timer()	= default;

	void			Reset();
	float			getDeltaTime();

private:
	decltype(std::chrono::high_resolution_clock::now()) start;

};

#endif
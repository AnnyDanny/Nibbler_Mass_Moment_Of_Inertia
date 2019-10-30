#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <SFML/System/Clock.hpp>

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
	sf::Clock		clock;

};

#endif
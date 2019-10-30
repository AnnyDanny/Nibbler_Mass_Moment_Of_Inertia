#include "../include/Timer.hpp"

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	clock.restart();
}

float Timer::getDeltaTime()
{
	return clock.getElapsedTime().asSeconds();
}

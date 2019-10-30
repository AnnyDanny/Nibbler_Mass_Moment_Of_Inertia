#include "../include/Timer.hpp"

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	start = std::chrono::high_resolution_clock::now();
}

float Timer::getDeltaTime()
{
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<float>(end - start).count();
}

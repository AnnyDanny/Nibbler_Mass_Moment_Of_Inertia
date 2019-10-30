#include "../include/Timer.hpp"

Timer* Timer::sInstance = nullptr;

Timer *Timer::Instance(){

	if (sInstance == NULL){
		sInstance = new Timer();
	}
	return sInstance;
}

void Timer::Release(){
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer(){
	Reset();
	mTimeScale = 0.0f;
}

Timer::~Timer(){}

void Timer::Reset(){
	mStartTicks = SDL_GetTicks();
	mElapseTicks = 0.0f;
	mDeltaTime = 0.0f;
}

float Timer::getDeltaTime(){
	return mDeltaTime;
}

void Timer::Update(){
	mElapseTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapseTicks * 0.001f;
}
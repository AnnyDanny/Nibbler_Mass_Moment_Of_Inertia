#include "StartScreen.hpp"
#include <iostream>
#include <thread>
#include <chrono>

//=================================================================================================
// StartScreen
//-------------------------------------------------------------------------------------------------
StartScreen::StartScreen(int32_t _screenWidth, int32_t _screenHeigh)
{
	mScreenWidth	= _screenWidth;
	mScreenHeigh	= _screenHeigh;
	choiceMade		= false;
	choice			= 0;
	mScreenPos.push_back(Vector2(0.0f, 0.0f));
	mScreenPos.push_back(Vector2(mScreenWidth * 0.35f, 68.0f));
	mScreenPos.push_back(Vector2(mScreenWidth * 0.35f, 140.0f));
	mScreenPos.push_back(Vector2(mScreenWidth * 0.35f, 212.0f));
	mScreenPos.push_back(Vector2(mScreenWidth * 0.18f, 85.0f));

}
//=================================================================================================
// Update
//-------------------------------------------------------------------------------------------------
void StartScreen::Update(const std::string& _inputKey)
{
	if (_inputKey == "UP" && choice > 0)
	{
		mScreenPos.back() += Vector2(0.0f, -72.0f);
		--choice;
	}
	else if (_inputKey == "DOWN" && choice < 2)
	{
		mScreenPos.back() += Vector2(0.0f, 72.0f);
		++choice;
	}
	else if (_inputKey == "ENTER")
	{
		choiceMade = true;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
//=================================================================================================
// ChoiceMade
//-------------------------------------------------------------------------------------------------
bool StartScreen::ChoiceMade() const
{
	return choiceMade;
}
//=================================================================================================
// Choice
//-------------------------------------------------------------------------------------------------
int8_t StartScreen::Choice() const
{
	return choice;
}
//=================================================================================================
// ScreenPos
//-------------------------------------------------------------------------------------------------
const std::vector<Vector2>&	StartScreen::ScreenPos()
{
	return mScreenPos;
}
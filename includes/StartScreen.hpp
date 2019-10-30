#ifndef _START_SCREEN_
#define _START_SCREEN_

#include "Collider.hpp"

class StartScreen
{
public:
	StartScreen(int32_t ScreenWidth, int32_t ScreenHeigh);
	StartScreen(const StartScreen&)	= default;
	virtual ~StartScreen()			= default;

	StartScreen&					operator=(const StartScreen&) = default;

	void							Update(const std::string& inputKey);
	bool							ChoiceMade()	const;
	int8_t							Choice()		const;
	const std::vector<Vector2>&		ScreenPos();

protected:
	int32_t							mScreenWidth;
	int32_t							mScreenHeigh;
	bool							choiceMade;
	int8_t							choice;
	std::vector<Vector2>			mScreenPos;
};

#endif // START_SCREEN

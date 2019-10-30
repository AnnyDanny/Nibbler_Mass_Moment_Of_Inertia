#ifndef _GMANAGER_HPP
#define _GMANAGER_HPP

#include "Food.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "StartScreen.hpp"
#include "Wall.hpp"
#include "INibblerGame.hpp"
#include "iNibblerAudio.hpp"
#include <memory>

//**************************************************************************************************
//	gManager
//--------------------------------------------------------------------------------------------------
class gManager
{
	enum KeyCodes : int8_t
	{
		KEY_W		= 1,
		KEY_A		= 2,
		KEY_S		= 3,
		KEY_D		= 4,
		KEY_SPACE	= 5,
		KEY_1		= 6,
		KEY_2		= 7,
		KEY_3		= 8,
		KEYPAD8		= 9,
		KEYPAD4		= 10,
		KEYPAD2		= 11,
		KEYPAD6		= 12,
	};
	enum SOLib : int8_t
	{
		NCURSES_LIB = 1,
		SDL_LIB	,
		SFML_LIB,
		
	};
public:
	gManager(bool is_dynamic_switching_enabled);
	~gManager();

	bool				Init(int32_t width, int32_t height, int8_t libNum);
	void 				run();

private:
	bool				LoadDLL(const std::string& dllName);
	void				InitSystems();
	void				InitPlayer();
	void				InitPlayerFromMap();
	void				SetWallsPosition();
	void				InitWalls();
	void				InitFood();
	void				InitText();

	void				Update();
	void				UpdateStartScreen();
	bool				HandlePlayerInput();
	bool				HandleSecondPlayerInput();
	void				CheckCollision();
	void				ManagePlayersDeath();
	void				PlayStartScreen();


	const int 							FrameRate = 60;
	bool 								_isRunning;
	bool 								_is_dynamic_switching_enabled;
	bool 								isTwoPlayersGame;
	int32_t								mScreenWidth;
	int32_t								mScreenHeight;
	SOLib								libChoice;
	//Game Staff --------------------------------------------
	std::unique_ptr<Level>				mLevel; // make a vector of levels
	std::unique_ptr<Player>				mPlayer;
	std::unique_ptr<Player>				mSecondPlayer;
	std::unique_ptr<Food>				mFood;
	std::vector<std::unique_ptr<Wall>>	mWalls;
	std::unique_ptr<StartScreen>		mStartScreen;
	//dll's staff ---------------------------------------
	void*								handle;
	char*								mError;

	create_t*							DLL_INIT		= nullptr;
	destroy_t*							DLL_DESTOY		= nullptr;
	INibblerGame*						DLL_Class		= nullptr;

	void*								handleAudio;
	create_audio*						AUDIO_INIT		= nullptr;
	destroy_audio*						AUDIO_DESTROY	= nullptr;
	INibblerAudio*						AUDIO_CLASS		= nullptr;
};

#endif

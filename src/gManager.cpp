#include "gManager.hpp"
#include <dlfcn.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

gManager::gManager(bool is_dynamic_switching_enabled) : _is_dynamic_switching_enabled(is_dynamic_switching_enabled)
{
	_isRunning			= true;
	isTwoPlayersGame	= false;
}

gManager::~gManager()
{
	if (DLL_DESTOY && DLL_Class && handle) {
		DLL_DESTOY(DLL_Class);
		dlclose(handle);
		mWalls.clear();
	}
}
//=================================================================================================
//	Init
//-------------------------------------------------------------------------------------------------
bool gManager::Init(int32_t _width, int32_t _height, int8_t libNum)
{
	mScreenWidth	= _width;
	mScreenHeight	= _height;
	libChoice		= static_cast<SOLib>(libNum);
	switch (libChoice)
	{
		case NCURSES_LIB:
			handle = dlopen("./ncurses_dll/libncurses.so", RTLD_LAZY);
			break;
		case SDL_LIB:
			handle = dlopen("./sdl_dll/libsdl.so", RTLD_LAZY);
			break;
		case SFML_LIB:
			handle = dlopen("./sfml_dll/libsfml.so", RTLD_LAZY);
			break;
	}
	if (!handle)
	{
		std::cerr << "Error " << dlerror() << "\n";
		return false;
	}
	DLL_INIT = (create_t*)dlsym(handle, "createINibblerEntity");
	mError = dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
	}
	DLL_DESTOY	= (destroy_t*)dlsym(handle, "deletINibblerEntity");
	mError		= dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
	}
	DLL_Class = DLL_INIT();
	if(!DLL_Class)
	{
		std::cout << "DLL init error\n";
		return false;
	}

	//=================================================================================================
	//	Audio Init
	//-------------------------------------------------------------------------------------------------

	handleAudio = dlopen("./audio_dll/audio.so", RTLD_LAZY);
	if (!handleAudio)
	{
		std::cerr << "Error" << dlerror() << "\n";
		return false;
	}
	AUDIO_INIT = (create_audio*)dlsym(handleAudio, "createAudioEntity");
	mError = dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
	}
	AUDIO_DESTROY	= (destroy_audio*)dlsym(handleAudio, "deletAudioEntity");
	mError		= dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
	}
	AUDIO_CLASS = AUDIO_INIT();
	if(!AUDIO_CLASS)
	{
		std::cout << "AUDIO_CLASS init error\n";
		return false;
	}
	std::cout << "InitSystems Init" << std::endl;
	return DLL_Class->InitSystems(mScreenWidth, mScreenHeight) && AUDIO_CLASS->Init();
}
//=================================================================================================
//	InitSystems
//-------------------------------------------------------------------------------------------------
void gManager::InitSystems()
{
	std::cout << "InitSystems" << std::endl;
	mLevel			= std::make_unique<Level>();
	mLevel->LoadLevel("map1.txt");
	mLevel->ParseLevel();

	mPlayer			= std::make_unique<Player>();
	mSecondPlayer	= std::make_unique<Player>();
	std::cout << "Lw: " << mLevel->LevelWidth() << " Lh: " << mLevel->LevelHeight() <<"\n";
	InitPlayerFromMap();
	InitPlayer();
	//------
	mFood			= std::make_unique<Food>(Vector2(64.0f, 64.0f), 32, 32);
	mFood->SetRespawnDementions(mLevel->LevelWidth(), mLevel->LevelHeight(), mLevel->LevelMap());
	InitFood();
	SetWallsPosition();
	InitWalls();
	InitText();
}
//=================================================================================================
//	InitPlayer
//-------------------------------------------------------------------------------------------------
void gManager::InitPlayer()
{
	for(size_t i = 0; i < mPlayer->PlayerPos().size(); ++i)
	{
		DLL_Class->AddPlayerTextureToRender("snake.png", 64, 32, 32, 32, mPlayer->PlayerPos()[i].x, mPlayer->PlayerPos()[i].y, 1);
	}
	if(isTwoPlayersGame)
	{
		for(size_t i = 0; i < mSecondPlayer->PlayerPos().size(); ++i)
		{
			DLL_Class->AddPlayerTextureToRender("snake2.png", 64, 32, 32, 32, mSecondPlayer->PlayerPos()[i].x + 64, mSecondPlayer->PlayerPos()[i].y, 2);
		}
	}
}
//=================================================================================================
//	InitPlayerFromMap
//-------------------------------------------------------------------------------------------------
void gManager::InitPlayerFromMap()
{
	for(size_t i = 0; i < mLevel->FirstPlayerPositions().size(); ++i)
	{
		mPlayer->Init(mLevel->FirstPlayerPositions()[i]);
	}
	if(isTwoPlayersGame)
	{
		for(size_t i = 0; i < mLevel->SecondPlayerPositions().size(); ++i)
		{
			mSecondPlayer->Init(mLevel->SecondPlayerPositions()[i]);
		}
	}
}
//=================================================================================================
//	SetWallsPosition
//-------------------------------------------------------------------------------------------------
void gManager::SetWallsPosition()
{
	for(size_t i = 0; i < mLevel->WallsPosition().size(); ++i)
	{
		mWalls.emplace_back(std::make_unique<Wall>(mLevel->WallsPosition()[i].first, 0, 0, 32, 32));
	}
}
//=================================================================================================
//	InitWalls
//-------------------------------------------------------------------------------------------------
void gManager::InitWalls()
{
	DLL_Class->AddObjectTextureToRender("back_grass.png", 0, 0, mLevel->LevelWidth(), mLevel->LevelHeight(), 0, 0);
	//DLL_Class->AddObjectTextureToRender("back_grass.png", 32, 32, mLevel->LevelWidth(), mLevel->LevelHeight(), 32, 32);
	for(size_t i = 0; i < mLevel->WallsPosition().size(); ++i)
	{
		DLL_Class->AddObjectTextureToRender(mLevel->WallsPosition()[i].second, 0, 0, 32, 32, mLevel->WallsPosition()[i].first.x, mLevel->WallsPosition()[i].first.y);
	}
}
//=================================================================================================
//	InitFood
//-------------------------------------------------------------------------------------------------
void gManager::InitFood()
{
	DLL_Class->AddFoodTextureToRender("snake.png", 0, 96, 32, 32, mFood->Position().x, mFood->Position().y);
}
//=================================================================================================
//	InitFood
//-------------------------------------------------------------------------------------------------
void gManager::InitText()
{
	DLL_Class->AddTextToRender("1 UP SCORE", 24, 200, 10, 10, mScreenWidth - 10, 10);
	DLL_Class->AddTextToRender(std::to_string(mPlayer->Score()), 24, 200, 200, 200, mScreenWidth + 10, 36);
	DLL_Class->AddTextToRender("2 UP SCORE", 24, 200, 10, 10, mScreenWidth - 10, 100);
	DLL_Class->AddTextToRender(std::to_string(mSecondPlayer->Score()), 24, 200, 200, 200, mScreenWidth + 10, 130);
}
//=================================================================================================
//	Update
//-------------------------------------------------------------------------------------------------
void gManager::Update()
{
	if(mPlayer->IsAlive())
	{
		DLL_Class->UpdatePlayerScore(std::to_string(mPlayer->Score()), 1, 1);
		mPlayer->Update();
		for(size_t i = 0; i < mPlayer->PlayerPos().size(); ++i)
		{
			DLL_Class->UpdatePlayerPos(mPlayer->PlayerPos()[i].x, mPlayer->PlayerPos()[i].y, i, 1);
			DLL_Class->UpdatePlayerTexture(mPlayer->TexturePos()[i].x, mPlayer->TexturePos()[i].y, i, 1);
		}
	}
	if(isTwoPlayersGame && mSecondPlayer->IsAlive())
	{
		mSecondPlayer->Update();
		DLL_Class->UpdatePlayerScore(std::to_string(mSecondPlayer->Score()), 3, 2);
		for(size_t i = 0; i < mSecondPlayer->PlayerPos().size(); ++i)
		{
			DLL_Class->UpdatePlayerPos(mSecondPlayer->PlayerPos()[i].x, mSecondPlayer->PlayerPos()[i].y, i, 2);
			DLL_Class->UpdatePlayerTexture(mSecondPlayer->TexturePos()[i].x, mSecondPlayer->TexturePos()[i].y, i, 2);
		}
	}
}
//=================================================================================================
//	UpdateStartScreen
//-------------------------------------------------------------------------------------------------
void gManager::UpdateStartScreen()
{
	for(size_t i = 0; i < mStartScreen->ScreenPos().size(); ++i)
	{
		DLL_Class->UpdateScreenPos(mStartScreen->ScreenPos()[i].x, mStartScreen->ScreenPos()[i].y, i);
	}
}
//=================================================================================================
// CheckCollision
//-------------------------------------------------------------------------------------------------
void gManager::CheckCollision()
{
	for (auto& wall : mWalls)
	{
		if (mPlayer->IsAlive() && mPlayer->CheckCircleCollision(*mPlayer, *wall))
		{
			mPlayer->Collide(*wall, mFood->FoodValue());
		}
		if(isTwoPlayersGame && mSecondPlayer->IsAlive() && mSecondPlayer->CheckCircleCollision(*mSecondPlayer, *wall))
		{
			mSecondPlayer->Collide(*wall, mFood->FoodValue());
		}
	}
	if (mPlayer->IsAlive() && mPlayer->CheckCircleCollision(*mPlayer, *mFood))
	{
		AUDIO_CLASS->PlaySFX("apple_eat2.wav");
		DLL_Class->AddPlayerTextureToRender("snake.png", 0, 0, 32, 32, 0, 0, 1);
		mPlayer->Collide(*mFood, mFood->FoodValue());
		mFood->ReSpawn();
		DLL_Class->UpdateFoodPos(mFood->Position().x, mFood->Position().y, 0);

	}
	if(isTwoPlayersGame && mSecondPlayer->IsAlive() && mSecondPlayer->CheckCircleCollision(*mSecondPlayer, *mFood))
	{
		AUDIO_CLASS->PlaySFX("apple_eat2.wav");
		DLL_Class->AddPlayerTextureToRender("snake2.png", 0, 0, 32, 32, 0, 0, 2);
		mSecondPlayer->Collide(*mFood, mFood->FoodValue());
		mFood->ReSpawn();
		DLL_Class->UpdateFoodPos(mFood->Position().x, mFood->Position().y, 0);
	}

	if (mPlayer->IsAlive() && ( isTwoPlayersGame && mSecondPlayer->IsAlive()))
	{
		for(std::size_t i = 0; i < mSecondPlayer->PlayerPos().size(); ++i)
		{
			if(mPlayer->CheckCircleCollision(*mPlayer, mSecondPlayer->Position(), 16))
			{
				mPlayer->IsAlive(false);
				mSecondPlayer->IsAlive(false);
				break;
			}
		}
	}
}

//=================================================================================================
// ManagePlayersDeath
//-------------------------------------------------------------------------------------------------
void gManager::ManagePlayersDeath()
{
	if (!mPlayer->IsAlive() && !mPlayer->IsDead())
	{
		mPlayer->IsDead(true);
		for(std::size_t i = 0; i < mPlayer->PlayerPos().size(); ++i)
		{
			DLL_Class->UpdatePlayerPos(-32.0f, -32.0, i, 1);
		}
	}
	if(isTwoPlayersGame && !mSecondPlayer->IsAlive() && !mSecondPlayer->IsDead())
	{
		mSecondPlayer->IsDead(true);
		for(std::size_t i = 0; i < mSecondPlayer->PlayerPos().size(); ++i)
		{
			DLL_Class->UpdatePlayerPos(-32.0f, -32.0, i, 2);
		}
	}
}

//=================================================================================================
// LoadDLL
//-------------------------------------------------------------------------------------------------
bool gManager::LoadDLL(const std::string& _dllName)
{
	DLL_DESTOY(DLL_Class);
	dlclose(handle);
	DLL_Class = nullptr;

	handle = dlopen(_dllName.c_str(), RTLD_LAZY);
	if (!handle)
	{
		std::cerr << "Error " << dlerror() << "\n";
		return false;
		exit(-1);
	}
	DLL_INIT	= (create_t*)dlsym(handle, "createINibblerEntity");
	mError		= dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
		exit(-1);
	}
	DLL_DESTOY	= (destroy_t*)dlsym(handle, "deletINibblerEntity");
	mError		= dlerror();
	if(mError)
	{
		std::cerr << "Error" << mError << "\n";
		return false;
		exit(-1);
	}
	DLL_Class = DLL_INIT();
	if(!DLL_Class)
	{
		std::cout << "DLL init error\n";
		return false;
		exit(-1);
	}
	if (!DLL_Class->InitSystems(mScreenWidth, mScreenHeight))
	{	
		return false;
	}
	InitPlayer();
	InitFood();
	SetWallsPosition();
	InitWalls();
	InitText();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	return true;
}
//=================================================================================================
// HandlePlayerInput
//-------------------------------------------------------------------------------------------------
bool gManager::HandlePlayerInput()
{
	if (DLL_Class->HandleInput(KEY_W) && mPlayer->HeadDir() != DOWN_DIR)
	{
		mPlayer->HeadDir(UP_DIR);
		mPlayer->RotateHead(96, 0);

	}
	else if (DLL_Class->HandleInput(KEY_S) && mPlayer->HeadDir() != UP_DIR)
	{
		mPlayer->HeadDir(DOWN_DIR);
		mPlayer->RotateHead(128, 32);
	}
	else if (DLL_Class->HandleInput(KEY_D) && mPlayer->HeadDir() != LEFT_DIR)
	{
		mPlayer->HeadDir(RIGHT_DIR);
		mPlayer->RotateHead(128, 0);
	}
	else if (DLL_Class->HandleInput(KEY_A) && mPlayer->HeadDir() != RIGHT_DIR)
	{
		mPlayer->HeadDir(LEFT_DIR);
		mPlayer->RotateHead(96, 32);
	}
	else if(DLL_Class->HandleInput(KEY_1) && _is_dynamic_switching_enabled)
	{
		if(!LoadDLL("./sdl_dll/libsdl.so"))
		{
			return false;
		}
	}
	else if(DLL_Class->HandleInput(KEY_2) && _is_dynamic_switching_enabled)
	{
		if(!LoadDLL("./sfml_dll/libsfml.so"))
		{
			return false;
		}
	}
	else if(DLL_Class->HandleInput(KEY_3) && _is_dynamic_switching_enabled)
	{
		if (!LoadDLL("./ncurses_dll/libncurses.so"))
		{
			return false;
		}
	}
	return true;
}
//=================================================================================================
// HandleSecondPlayerInput
//-------------------------------------------------------------------------------------------------
bool gManager::HandleSecondPlayerInput()
{
	if (DLL_Class->HandleInput(KEYPAD8) && mSecondPlayer->HeadDir() != DOWN_DIR)
	{
		mSecondPlayer->HeadDir(UP_DIR);
		mSecondPlayer->RotateHead(96, 0);
		return true;
	}
	else if (DLL_Class->HandleInput(KEYPAD2) && mSecondPlayer->HeadDir() != UP_DIR)
	{
		mSecondPlayer->HeadDir(DOWN_DIR);
		mSecondPlayer->RotateHead(128, 32);
		return true;
	}
	else if (DLL_Class->HandleInput(KEYPAD6) && mSecondPlayer->HeadDir() != LEFT_DIR)
	{
		mSecondPlayer->HeadDir(RIGHT_DIR);
		mSecondPlayer->RotateHead(128, 0);
		return true;
	}
	else if (DLL_Class->HandleInput(KEYPAD4) && mSecondPlayer->HeadDir() != RIGHT_DIR)
	{
		mSecondPlayer->HeadDir(LEFT_DIR);
		mSecondPlayer->RotateHead(96, 32);
		return true;
	}
	return true;
}
//=================================================================================================
// PlayStartScreen
//-------------------------------------------------------------------------------------------------
void gManager::PlayStartScreen()
{
	mStartScreen = std::make_unique<StartScreen>(mScreenWidth, mScreenHeight);
	if(libChoice == SOLib::SDL_LIB || libChoice == SOLib::SFML_LIB)
	{
		DLL_Class->AddScreenTextureToRender("back.jpg", 0, 0, mScreenWidth + 200, mScreenHeight, 0, 0);
		DLL_Class->AddScreenTextureToRender("1player.png", 0, 0, 239, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender("2player.png", 0, 0, 239, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender("quit.png", 0, 0, 239, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender("SnakeArrow.png", 0, 0, 112, 32, 0, 0);
	}
	else
	{
		DLL_Class->AddScreenTextureToRender("", 0, 0, 0, 0, 0, 0);
		DLL_Class->AddScreenTextureToRender("1 player", 90, 130, 239, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender("2 player", 110, 130, 239, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender("quit", 120, 130, 0, 71, 0, 0);
		DLL_Class->AddScreenTextureToRender(">", 100, 80, 112, 32, 0, 0);
	}
	while (!mStartScreen->ChoiceMade() && _isRunning)
	{
		_isRunning = DLL_Class->HandleCloseEvent();
		if (DLL_Class->HandleInput(KEY_W))
		{
			mStartScreen->Update("UP");
		}
		else if (DLL_Class->HandleInput(KEY_S))
		{
			mStartScreen->Update("DOWN");
		}
		else if (DLL_Class->HandleInput(KEY_SPACE))
		{
			mStartScreen->Update("ENTER");
		}
		UpdateStartScreen();
		DLL_Class->PlayStartScreen(); // rendering
		DLL_Class->ClearBuffer();
		DLL_Class->Update();
	}
	if(!_isRunning)
	{
		return;
	}
	switch (mStartScreen->Choice())
	{
	case 0:	_isRunning = true;	break;
	case 1:	_isRunning = true;	isTwoPlayersGame = true;	break;
	case 2:	_isRunning = false;	break;
	default:_isRunning = false;	break;
	}
}
//=================================================================================================
// run
//-------------------------------------------------------------------------------------------------
void gManager::run()
{
	PlayStartScreen();
	InitSystems();
	AUDIO_CLASS->PlayMusic("back.wav");
	while (_isRunning)
	{
		_isRunning = DLL_Class->HandleCloseEvent();
		DLL_Class->UpdateTimer();

		if(!HandlePlayerInput())
		{
			break;
		}
		
		if(isTwoPlayersGame)
		{
			if(!HandleSecondPlayerInput())
			{
				break;
			}
		}
		if (DLL_Class->GetDeltaTime() >= (20.0f / FrameRate) && _isRunning && DLL_Class)
		{
		 	DLL_Class->ClearBuffer();
			CheckCollision();
			Update();
			if(!mPlayer->IsAlive() && (isTwoPlayersGame && !mSecondPlayer->IsAlive()))
			{
				break;
			}
			if(!mPlayer->IsAlive() && !isTwoPlayersGame)
			{
				break;
			}
			ManagePlayersDeath();
		 	DLL_Class->Render();
			DLL_Class->ResetTimer();
		}
		DLL_Class->Update();
	}
	AUDIO_CLASS->StopMusic();
}

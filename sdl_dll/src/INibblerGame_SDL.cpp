#include "../include/INibblerGame_SDL.hpp"

#define EXPORT __attribute__((visibility("default")))

EXPORT INibblerGame_SDL::INibblerGame_SDL()
{
	mTimer			= Timer::Instance();
	mGraphics		= Graphics::Instance();
	mInputManager	= InputManager::Instance();
}

EXPORT INibblerGame_SDL::~INibblerGame_SDL()
{
	Timer::Release();
	mTimer = nullptr;
	Graphics::Release();
	mGraphics = nullptr;
	InputManager::Release();
	mInputManager = nullptr;
	//AssetManager::Release();
}
//==================================================================================================
//	InitSystems
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_SDL::InitSystems(int32_t _ScreenWidth, int32_t _ScreenHeigh)
{
	return mGraphics->Init(_ScreenWidth, _ScreenHeigh);
}
//==================================================================================================
//	PlayStartScreen
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SDL::PlayStartScreen()
{
	for (size_t i = 0; i < StartScreenTextures.size(); ++i)
	{
		StartScreenTextures[i]->Render();
	}
	mGraphics->Render();
}
//==================================================================================================
//	GetDeltaTime
//--------------------------------------------------------------------------------------------------
EXPORT float	INibblerGame_SDL::GetDeltaTime()
{
	return mTimer->getDeltaTime();
}
//==================================================================================================
//	ResetTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SDL::ResetTimer()
{
	mTimer->Reset();
}
//==================================================================================================
//	UpdateTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SDL::UpdateTimer()
{
	mTimer->Update();
}
//==================================================================================================
//	Update
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SDL::Update()
{
	mInputManager->UpdatePrevInput();
}
//==================================================================================================
//	UpdatePlayerPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::UpdatePlayerPos(float xPos, float yPos, size_t index, uint8_t playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures[index]->SetPosition(xPos, yPos);
	}
	else
	{
		SecondPlayerTextures[index]->SetPosition(xPos, yPos);
	}
}
//==================================================================================================
//	UpdateFoodPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::UpdateFoodPos(float PosX, float PosY, size_t index)
{
	// maybe check size
	FoodTextures[index]->SetPosition(PosX, PosY);
}
//==================================================================================================
//	UpdatePlayerDir
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::UpdatePlayerTexture(int32_t xPos, int32_t yPos, size_t index, uint8_t playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures[index]->Rotate(xPos, yPos);
	}
	else
	{
		SecondPlayerTextures[index]->Rotate(xPos, yPos);
	}
}
//==================================================================================================
//	UpdatePlayerScore
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::UpdatePlayerScore(const std::string& score, size_t index, uint8_t playerNum)
{
	// todo
	if(playerNum == 1)
	{
		TextTextures[index]->UpdateTextTexture(score);
	}
	else
	{
		TextTextures[index]->UpdateTextTexture(score);
	}
}
//==================================================================================================
//	UpdateScreenPos
//--------------------------------------------------------------------------------------------------
EXPORT void	 INibblerGame_SDL::UpdateScreenPos(float xPos, float yPos, size_t index)
{
	StartScreenTextures[index]->SetPosition(xPos, yPos);
}
//==================================================================================================
//	HandleInput
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_SDL::HandleInput(int8_t keyCode)
{
	SDL_Scancode code = SDL_SCANCODE_UNKNOWN;
	switch(keyCode)
	{
		case 1: code = SDL_SCANCODE_W;		break;
		case 2: code = SDL_SCANCODE_A;		break;
		case 3: code = SDL_SCANCODE_S;		break;
		case 4: code = SDL_SCANCODE_D;		break;
		case 5: code = SDL_SCANCODE_SPACE;	break;
		case 6: code = SDL_SCANCODE_1; 		break;
		case 7: code = SDL_SCANCODE_2; 		break;
		case 8: code = SDL_SCANCODE_3; 		break;
		case 9: code = SDL_SCANCODE_KP_8; 	break;
		case 10: code = SDL_SCANCODE_KP_4;	break;
		case 11: code = SDL_SCANCODE_KP_2;	break;
		case 12: code = SDL_SCANCODE_KP_6;	break;
	}
	return mInputManager->KeyPressed(code) ? true : false;
}
//==================================================================================================
//	HandleCloseEvent
//--------------------------------------------------------------------------------------------------
EXPORT bool INibblerGame_SDL::HandleCloseEvent()
{
	while (SDL_PollEvent(&mEvent) != 0)
	{
		if (mEvent.type == SDL_QUIT || (mEvent.type == SDL_KEYDOWN && mEvent.key.keysym.sym == SDLK_ESCAPE))
		{
			return false;
		}
	}
	return true;
}
//==================================================================================================
//	Render
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::Render()
{
	for (size_t i = 0; i < ObjectTextures.size(); ++i)
	{
		ObjectTextures[i]->Render();
	}
	for (size_t i = 0; i < FoodTextures.size(); ++i)
	{
		FoodTextures[i]->Render();
	}
	
	for (size_t i = 0; i < PlayerTextures.size(); ++i)
	{
		PlayerTextures[i]->Render();
	}
	for (size_t i = 0; i < SecondPlayerTextures.size(); ++i)
	{
		SecondPlayerTextures[i]->Render();
	}

	for (size_t i = 0; i < TextTextures.size(); ++i)
	{
		TextTextures[i]->Render();
	}
	mGraphics->Render();
}
//==================================================================================================
//	ClearBuffer
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::ClearBuffer()
{
	mGraphics->ClearBuffer();
}
//==================================================================================================
//	AddPlayerTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::AddPlayerTextureToRender(const std::string&	_filePath,
													   int32_t				x,
													   int32_t				y,
													   int32_t				textureW,
													   int32_t				textureH,
													   float				xPos,
													   float				yPos,
													   uint8_t				playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures.push_back(std::make_unique<Texture>(_filePath, x, y, textureW, textureH, xPos, yPos));
	}
	else
	{
		SecondPlayerTextures.push_back(std::make_unique<Texture>(_filePath, x, y, textureW, textureH, xPos, yPos));
	}
}
//==================================================================================================
//	AddObjectTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::AddObjectTextureToRender(const std::string&	_filePath,
													   int32_t				x,
													   int32_t				y,
													   int32_t				textureW,
													   int32_t				textureH,
													   float				xPos,
													   float				yPos)		
{
	ObjectTextures.push_back(std::make_unique<Texture>(_filePath, x, y, textureW, textureH, xPos, yPos));;
}
//==================================================================================================
//	AddFoodTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::AddFoodTextureToRender(const std::string&		_filePath,
													 int32_t				x,
													 int32_t				y,
													 int32_t				textureW,
													 int32_t				textureH,
													 float					xPos,
													 float					yPos)
{
	FoodTextures.push_back(std::make_unique<Texture>(_filePath, x, y, textureW, textureH, xPos, yPos));
}
//==================================================================================================
//	AddScreenTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::AddScreenTextureToRender(const std::string&	_filePath,
											 		   int32_t				_x,
											 		   int32_t				_y,
											 		   int32_t				_textureW,
											 		   int32_t				_textureH,
											 		   float				_xPos,
											 		   float				_yPos)
{
	StartScreenTextures.push_back(std::make_unique<Texture>(_filePath, _x, _y, _textureW, _textureH, _xPos, _yPos));
}
//==================================================================================================
//	AddTextToRender
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SDL::AddTextToRender(const std::string& 	text,
											  uint8_t				fontSize,
											  uint8_t				r,
											  uint8_t				g,
											  uint8_t				b,
											  float					xPos,
											  float					yPos)
{
	TextTextures.push_back(std::make_unique<Texture>(text, "8bit.ttf", fontSize, r, g, b, xPos, yPos));
}
//==================================================================================================
//	SetReserveAmountofTextures
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SDL::SetReserveAmountofTextures(int32_t _amount)
{
	PlayerTextures.reserve(_amount);
	ObjectTextures.reserve(_amount);
}

EXPORT INibblerGame* createINibblerEntity()
{
	return new INibblerGame_SDL();
}

EXPORT void deletINibblerEntity(INibblerGame* entity)
{
	delete entity;
}
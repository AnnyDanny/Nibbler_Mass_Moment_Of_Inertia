#include "../include/INibblerGame_SFML.hpp"

#define EXPORT __attribute__((visibility("default")))

using std::cout;


EXPORT INibblerGame_SFML::INibblerGame_SFML()
{
	mTimer = std::make_unique<Timer>();
}

EXPORT INibblerGame_SFML::~INibblerGame_SFML()
{
	// if(mWindow)
	// {
		// delete mWindow;
		// exit(-1);
	// }
	// else {
	// 	std::cout << "Error dlopen" << std::endl;
	// 	exit(-1);
	// }
}
//==================================================================================================
//	InitSystems
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_SFML::InitSystems(int32_t _screenWidth, int32_t _screenHeigh)
{
	mScreenWidth 	= _screenWidth;
	mScreenHeight	= _screenHeigh;
	mWindow.create(sf::VideoMode(mScreenWidth + 200, mScreenHeight), "SFML Snake!");
	return true;
}
//==================================================================================================
//	PlayStartScreen
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SFML::PlayStartScreen()
{
	for (size_t i = 0; i < StartScreenTextures.size(); ++i)
	{
		StartScreenTextures[i]->Render(&mWindow);
	}
	mWindow.display();
}
//==================================================================================================
//	GetDeltaTime
//--------------------------------------------------------------------------------------------------
EXPORT float	INibblerGame_SFML::GetDeltaTime()
{
	return mTimer->getDeltaTime();
}
//==================================================================================================
//	ResetTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SFML::ResetTimer()
{
	mTimer->Reset();
}
//==================================================================================================
//	UpdateTimer
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SFML::UpdateTimer()
{
}
//==================================================================================================
//	Update
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SFML::Update()
{

}
//==================================================================================================
//	UpdatePlayerPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::UpdatePlayerPos(float xPos, float yPos, size_t index, uint8_t playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures[index]->Pos(sf::Vector2f(xPos, yPos));
	}
	else
	{
		SecondPlayerTextures[index]->Pos(sf::Vector2f(xPos, yPos));
	}
}
//==================================================================================================
//	UpdateFoodPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::UpdateFoodPos(float PosX, float PosY, size_t index)
{
	// maybe check size
	FoodTextures[index]->Pos(sf::Vector2f(PosX, PosY));
}
//==================================================================================================
//	UpdatePlayerDir
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::UpdatePlayerTexture(int32_t xPos, int32_t yPos, size_t index, uint8_t playerNum)
{
	if(playerNum == 1)
	{
		PlayerTextures[index]->Rotate(sf::IntRect(xPos, yPos, 32, 32));
	}
	else
	{
		SecondPlayerTextures[index]->Rotate(sf::IntRect(xPos, yPos, 32, 32));
	}
}
//==================================================================================================
//	UpdatePlayerScore
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::UpdatePlayerScore(const std::string& score, size_t index, uint8_t playerNum)
{
	TextTextures[index]->SetTextString(score);
}
//==================================================================================================
//	UpdateScreenPos
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::UpdateScreenPos(float PosX, float PosY, size_t index)
{
	StartScreenTextures[index]->Pos(sf::Vector2f(PosX, PosY));
}
//==================================================================================================
//	HandleInput
//--------------------------------------------------------------------------------------------------
EXPORT bool	INibblerGame_SFML::HandleInput(int8_t keyCode)
{
	sf::Keyboard::Key code = sf::Keyboard::Key::Unknown;
	switch(keyCode)
	{
		case 1: code = sf::Keyboard::Key::W;		break;
		case 2: code = sf::Keyboard::Key::A;		break;
		case 3: code = sf::Keyboard::Key::S;		break;
		case 4: code = sf::Keyboard::Key::D;		break;
		case 5: code = sf::Keyboard::Key::Space;	break;
		case 6: code = sf::Keyboard::Key::Num1;		break;
		case 7: code = sf::Keyboard::Key::Num2;		break;
		case 8: code = sf::Keyboard::Key::Num3;		break;
		case 9: code = sf::Keyboard::Key::Numpad8; 	break;
		case 10: code = sf::Keyboard::Key::Numpad4;	break;
		case 11: code = sf::Keyboard::Key::Numpad2;	break;
		case 12: code = sf::Keyboard::Key::Numpad6;	break;
	}
	return sf::Keyboard::isKeyPressed(code);
}
//==================================================================================================
//	HandleCloseEvent
//--------------------------------------------------------------------------------------------------
EXPORT bool INibblerGame_SFML::HandleCloseEvent()
{
	while (mWindow.pollEvent(mEvent) != 0)
	{
		if (mEvent.type == sf::Event::Closed) {
			system("echo \"HandleCloseEvent in if Event::Closed\" >> test_output");
			return false;
		}
		else if (mEvent.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			system("echo \"HandleCloseEvent in if Event::KeyPressed\" >> test_output");
			return false;
		}
	}
	return true;
}
//==================================================================================================
//	Render
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::Render()
{
	for (size_t i = 0; i < ObjectTextures.size(); ++i)
	{
		ObjectTextures[i]->Render(&mWindow);
	}
	for (size_t i = 0; i < FoodTextures.size(); ++i)
	{
		FoodTextures[i]->Render(&mWindow);
	}
	
	for (size_t i = 0; i < PlayerTextures.size(); ++i)
	{
		PlayerTextures[i]->Render(&mWindow);
	}

	for (size_t i = 0; i < TextTextures.size(); ++i)
	{
		TextTextures[i]->RenderText(&mWindow);
	}
	for (size_t i = 0; i < SecondPlayerTextures.size(); ++i)
	{
		SecondPlayerTextures[i]->Render(&mWindow);
	}
	mWindow.display();
}
//==================================================================================================
//	ClearBuffer
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::ClearBuffer()
{
	mWindow.clear();
}
//==================================================================================================
//	AddPlayerTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::AddPlayerTextureToRender(const std::string&	_filePath,
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
		PlayerTextures.push_back(std::make_unique<Texture>(_filePath,
														   sf::Vector2f(xPos, yPos),
														   sf::Vector2f(textureW, textureH),
														   sf::IntRect(static_cast<int32_t>(x), static_cast<int32_t>(y), 32, 32)));
	}
	else
	{
		SecondPlayerTextures.push_back(std::make_unique<Texture>(_filePath,
														   sf::Vector2f(xPos, yPos),
														   sf::Vector2f(textureW, textureH),
														   sf::IntRect(static_cast<int32_t>(x), static_cast<int32_t>(y), 32, 32)));
	
	}
}
//==================================================================================================
//	AddObjectTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::AddObjectTextureToRender(const std::string&	_filePath,
													   int32_t				x,
													   int32_t				y,
													   int32_t				textureW,
													   int32_t				textureH,
													   float				xPos,
													   float				yPos)		
{
	ObjectTextures.push_back(std::make_unique<Texture>(_filePath,
													   sf::Vector2f(xPos, yPos),
													   sf::Vector2f(textureW, textureH),
													   sf::IntRect(static_cast<int32_t>(x), static_cast<int32_t>(y), textureW, textureH)));
}
//==================================================================================================
//	AddFoodTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::AddFoodTextureToRender(const std::string&	_filePath,
													 int32_t				x,
													 int32_t				y,
													 int32_t				textureW,
													 int32_t				textureH,
													 float					xPos,
													 float					yPos)
{
	FoodTextures.push_back(std::make_unique<Texture>(_filePath,
													  sf::Vector2f(xPos, yPos),
													  sf::Vector2f(textureW, textureH),
													  sf::IntRect(static_cast<int32_t>(x), static_cast<int32_t>(y), 32, 32)));
}
//==================================================================================================
//	AddScreenTextureToRender
//--------------------------------------------------------------------------------------------------
EXPORT void INibblerGame_SFML::AddScreenTextureToRender(const std::string&	_filePath,
											 			int32_t				_x,
											 			int32_t				_y,
											 			int32_t				_textureW,
											 			int32_t				_textureH,
											 			float				_xPos,
											 			float				_yPos)
{
	StartScreenTextures.push_back(std::make_unique<Texture>(_filePath,
															sf::Vector2f(_xPos, _yPos),
															sf::Vector2f(_textureW, _textureH),
															sf::IntRect(static_cast<int32_t>(_x), static_cast<int32_t>(_y), _textureW, _textureH)));
}
//==================================================================================================
//	AddTextToRender
//--------------------------------------------------------------------------------------------------
EXPORT void	INibblerGame_SFML::AddTextToRender(const std::string&	_text,
											   uint8_t				_fontSize,
											   uint8_t				_r,
											   uint8_t				_g,
											   uint8_t				_b,
											   float				_xPos,
											   float				_yPos)
{
	TextTextures.push_back(std::make_unique<Texture>(_text,
													_fontSize,
													sf::Color(_r, _g, _b, 250),
													sf::Vector2f(_xPos, _yPos)));
}

EXPORT INibblerGame* createINibblerEntity()
{
	return new INibblerGame_SFML();
}

EXPORT void deletINibblerEntity(INibblerGame* entity)
{
	std::cout << "destroing!\n";
	delete entity;
}
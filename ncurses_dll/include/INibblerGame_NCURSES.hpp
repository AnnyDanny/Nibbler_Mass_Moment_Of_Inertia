#ifndef _INIBBLER_GAME_NCURSES_
#define _INIBBLER_GAME_NCURSES_

#include "../../includes/INibblerGame.hpp"
#include "../include/Texture.hpp"
#include "../include/Timer.hpp"
#include <vector>
#include <ncurses.h>

class INibblerGame_NCURSES : public INibblerGame
{
	using eInherited = INibblerGame;
public:
	void redrawBackground();


	INibblerGame_NCURSES();
	virtual ~INibblerGame_NCURSES();

	virtual bool	InitSystems(int32_t ScreenWidth, int32_t ScreenHeigh)				override;
	virtual void	PlayStartScreen()													override;

	virtual float	GetDeltaTime()														override;
	virtual void	ResetTimer()														override;
	virtual void	UpdateTimer()														override;

	virtual bool	HandleInput(int8_t keyCode)											override;
	virtual bool	HandleCloseEvent()													override;

	virtual void	Render()															override;
	virtual void	Update()															override;
	virtual void	UpdatePlayerPos(float PosX, float PosY, size_t index, uint8_t playerNum)	override;
	virtual void	UpdateFoodPos(float PosX, float PosY, size_t index)					override;
	virtual void	UpdatePlayerTexture(int32_t startX, int32_t startY, size_t index, uint8_t playerNum)	override;
	virtual void	UpdatePlayerScore(const std::string& score, size_t index, uint8_t playerNum)			override;
	virtual void	UpdateScreenPos(float xPos, float yPos, size_t index)				override;
	virtual void	ClearBuffer()														override;

	//path to texture, x,y - start point on picture(from where to start render), w,h - width/heigh
	virtual void	AddPlayerTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos,
											 uint8_t	playerNum)						override;
	// like walls and text on screen
	virtual void	AddObjectTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos)						override;
	virtual void	AddFoodTextureToRender(const		std::string& path,
										   int32_t		x,
										   int32_t		y,
										   int32_t		textureW,
										   int32_t		textureH,
										   float		xPos,
										   float		yPos)						override;
	virtual void	AddScreenTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos)						override;
	virtual void	AddTextToRender(const		std::string& text,
									uint8_t		fontSize,
									uint8_t		r,
									uint8_t		g,
									uint8_t		b,
									float		xPos,
									float		yPos)								override;


protected:
	//window staff
	int32_t				mScreenWidth;
	int32_t				mScreenHeight;
	WINDOW*				mWindow;

	std::unique_ptr<Timer>					mTimer;
	std::vector<std::unique_ptr<Texture>>	PlayerTextures; // for snake
	std::vector<std::unique_ptr<Texture>>	SecondPlayerTextures; // for snake
	std::vector<std::unique_ptr<Texture>>	ObjectTextures; // like walls
	std::vector<std::unique_ptr<Texture>>	StartScreenTextures; //
	std::vector<std::unique_ptr<Texture>>	TextTextures;
	std::vector<std::unique_ptr<Texture>>	FoodTextures; // must be only 2 textures, front for apple, back for other one for bonus with time respawn
};

extern "C" INibblerGame*	createINibblerEntity();

extern "C" void 			deletINibblerEntity(INibblerGame*);

#endif
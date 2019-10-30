#ifndef _INIBBLER_GAME_HPP_
#define _INIBBLER_GAME_HPP_

#include <iostream>

class INibblerGame
{
public:
	virtual			~INibblerGame() 												= default;
	
	virtual bool	InitSystems(int32_t ScreenWidth, int32_t ScreenHeigh)			= 0;
	virtual void	PlayStartScreen()												= 0;

	virtual float	GetDeltaTime()													= 0;
	virtual void	ResetTimer()													= 0;
	virtual void	UpdatePlayerPos(float xPos, float yPos, size_t index, uint8_t playerNum)			= 0;
	virtual void	UpdateFoodPos(float PosX, float PosY, size_t index)				= 0;
	virtual void	UpdatePlayerTexture(int32_t xDir, int32_t yDir, size_t index,  uint8_t playerNum)	= 0;
	virtual void	UpdatePlayerScore(const std::string& score, size_t index,  uint8_t playerNum)		= 0;
	virtual void	UpdateScreenPos(float xPos, float yPos, size_t index)			= 0;
	virtual void	UpdateTimer()													= 0;

	///$todo: return a texture from this funcs and make only 2 of them (for sfml need separatre)
	virtual void	AddPlayerTextureToRender(const std::string&	path,
											 int32_t			x,
											 int32_t			y,
											 int32_t			textureW,
											 int32_t			textureH,
											 float				xPos,
											 float				yPos,
											 uint8_t			playerNum)			= 0;
	virtual void	AddObjectTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos)						= 0;
	virtual void	AddFoodTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos)						= 0;
	virtual void	AddScreenTextureToRender(const		std::string& path,
											 int32_t	x,
											 int32_t	y,
											 int32_t	textureW,
											 int32_t	textureH,
											 float		xPos,
											 float		yPos)						= 0;
	virtual void	AddTextToRender(const		std::string& text,
									uint8_t		fontSize,
									uint8_t		r,
									uint8_t		g,
									uint8_t		b,
									float		xPos,
									float		yPos)								= 0;

	virtual void	Render()														= 0;
	virtual void	ClearBuffer()													= 0;

	virtual bool	HandleInput(int8_t keyCode)										= 0;
	virtual bool	HandleCloseEvent()												= 0;

	virtual void	Update()														= 0;
protected:

};

typedef INibblerGame*		create_t();
typedef void 				destroy_t(INibblerGame*);

#endif

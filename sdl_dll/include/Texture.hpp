#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include "Graphics.hpp"
#include <string>
#include <memory>

//**************************************************************************************************
//	Texture
//--------------------------------------------------------------------------------------------------
class Texture
{
public:
	//
	Texture(const std::string&	path,
			int32_t				startRenderingPosX,
			int32_t				startRenderingPosY,
			int32_t				textureW,
			int32_t				textureH,
			float				xPos,
			float				yPos);
	Texture(const std::string&	text,
			const std::string&	path,
			int 				size,
			char 				r,
			char 				g,
			char 				b,
			float 				xPos,
			float 				yPos);
	virtual ~Texture();

	void	Render();
	void	SetPosition(float x, float y);
	// actuallt it's now a rotating, it's just changing rendering rect
	void	Rotate(int x, int y) { mClipRect.x = x; mClipRect.y = y; }
	void	UpdateTextTexture(const std::string& text);

protected:
	SDL_Texture*	GetTexture(std::string filename);
	SDL_Texture*	GetText(std::string text, std::string filename, int size, Uint8 r, Uint8 g, Uint8 b);
	
	TTF_Font*		GetFont(std::string filename, int size);

	char 			r;
	char 			g;
	char 			b;
	int32_t			textSize;
	std::string		path;

	float			xPos;
	float			yPos;
	int32_t			mWidth;
	int32_t			mHeight;
	bool			mClipped;
	float			mRotation;

	SDL_Rect		mRenderRect;
	SDL_Rect		mClipRect;
	SDL_Texture*	mTex;
	TTF_Font*		mFont;
	Graphics*		mGraphics; //singeltone
};

#endif
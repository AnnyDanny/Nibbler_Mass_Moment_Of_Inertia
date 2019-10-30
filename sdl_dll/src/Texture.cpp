#include "../include/Texture.hpp"

// for text
Texture::Texture(const std::string& text, const std::string& _path, int size, char red, char green, char blue, float _xPos, float	_yPos)
{
	mGraphics		= Graphics::Instance();
	mTex			= GetText(text, _path, size, red, green, blue);

	mClipped		= false;
	mRotation		= 0.0f;
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	mRenderRect.w	= mWidth;
	mRenderRect.h	= mHeight;
	xPos			= _xPos;
	yPos			= _yPos;

	r			= red;
	g			= green;
	b			= blue;
	textSize	= size;
	path		= _path;
}
//=============================================================================
//	Texture
//-----------------------------------------------------------------------------
Texture::Texture(const std::string&	_path,
				 int32_t			_startRenderingPosX,
				 int32_t			_startRenderingPosY,
				 int32_t			_textureW,
				 int32_t			_textureH,
				 float				_xPos,
				 float				_yPos)
{
	xPos			= _xPos;
	yPos			= _yPos;
	mGraphics		= Graphics::Instance();
	mTex			= GetTexture(_path);
	mClipped 		= true;
	mWidth			= _textureW;
	mHeight			= _textureH;
	mRenderRect.w	= mWidth;
	mRenderRect.h	= mHeight;
	mClipRect.x		= _startRenderingPosX;
	mClipRect.y		= _startRenderingPosY;
	mClipRect.w		= mWidth;
	mClipRect.h		= mHeight;
}
Texture::~Texture()
{
	mGraphics	= nullptr;
	if(mTex)
	{
		SDL_DestroyTexture(mTex);
		mTex		= nullptr;
	}
	// if(mFont)
	// {
	// 	TTF_CloseFont(mFont);
	// }
}
//=============================================================================
//	UpdateTextTexture
//-----------------------------------------------------------------------------
void Texture::UpdateTextTexture(const std::string& text)
{
	if(mTex)
	{
		SDL_DestroyTexture(mTex);
		mTex 			= nullptr;
		mTex 			= GetText(text, "8bit.ttf", textSize, r, g, b);
		mWidth 			= text.size() - 1 == 0 ? textSize : (text.size() - 1) * textSize;
		mHeight 		= textSize;
		mRenderRect.w	= mWidth;
		mRenderRect.h	= mHeight;
	}
}
//=============================================================================
//	SetPosition
//-----------------------------------------------------------------------------
void Texture::SetPosition(float x, float y)
{
	xPos = x;
	yPos = y;
}
//=============================================================================
//	Render
//-----------------------------------------------------------------------------
void Texture::Render()
{
	mRenderRect.x = static_cast<int32_t>(xPos);
	mRenderRect.y = static_cast<int32_t>(yPos);
	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
	mGraphics->DrawTexture(mTex, (mClipped)? &mClipRect : NULL , &mRenderRect);
}
//=============================================================================
//	GetTexture
//-----------------------------------------------------------------------------
SDL_Texture* Texture::GetTexture(std::string filename)
{
	std::string fullpath;
	fullpath.append("resourses/sprites/" + filename);
	SDL_Texture* texture = nullptr;
	
	texture = Graphics::Instance()->LoadTexture(fullpath);
	return texture;
}
//=============================================================================
//	GetFont
//-----------------------------------------------------------------------------
TTF_Font* Texture::GetFont(std::string filename, int size)
{
	std::string fullpath;
	fullpath.append("resourses/fonts/" + filename);

	TTF_Font* font = nullptr;
	font = TTF_OpenFont(fullpath.c_str(), size);
	if (font == nullptr)
	{
		std::cout << "Error opening " << fullpath << "font " << TTF_GetError() << std::endl;
	}
	return font;
}
//=============================================================================
//	GetText
//-----------------------------------------------------------------------------
SDL_Texture* Texture::GetText(std::string text, std::string filename, int size, Uint8 r, Uint8 g, Uint8 b)
{
	std::string fullpath;
	fullpath.append("resourses/fonts/" + filename);

	TTF_Font* font 			= GetFont(filename, size);
	SDL_Texture* texture	= nullptr;

	if(font)
	{
		texture = Graphics::Instance()->CreateTTF(font, text, r, g, b);
		TTF_CloseFont(font);
	}
	return texture;
}

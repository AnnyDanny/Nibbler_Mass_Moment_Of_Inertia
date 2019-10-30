#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include <SDL2/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <string>
#include <iostream>
class AssetManager;
//**************************************************************************************************
//	Graphics
//--------------------------------------------------------------------------------------------------
class Graphics
{
public:
	static Graphics*	Instance();
	static void			Release();

	bool				Init(int32_t screenWidth, int32_t screenHeight);

	SDL_Texture*		CreateTTF(TTF_Font* font, std::string text, Uint8 r, Uint8 g, Uint8 b);
	SDL_Texture*		LoadTexture(std::string const& path);

	void 				ClearBuffer();
	void 				DrawTexture(SDL_Texture *tex, SDL_Rect *clip = NULL ,SDL_Rect *rend = NULL);
	void 				Render();

private:
	Graphics();
	~Graphics();

	static Graphics*	sInstance;
	int32_t				mScreenWidth;
	int32_t				mScreenHeight;

	SDL_Window*			mWindow;
	SDL_Renderer*		mRenderer;
};

#endif
#include "../include/Graphics.hpp"

Graphics* Graphics::sInstance = nullptr;

//**************************************************************************************************
//	Graphics::Instance
//--------------------------------------------------------------------------------------------------
Graphics* Graphics::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Graphics();
	}
	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

Graphics::Graphics()
{
	mWindow			= nullptr;
	//by default
	mScreenWidth	= 640;
	mScreenHeight 	= 480;
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
//==================================================================================================
//	Graphics::Init
//--------------------------------------------------------------------------------------------------
bool Graphics::Init(int32_t _screenWidth, int32_t _screenHeight)
{
	mScreenWidth 	= _screenWidth;
	mScreenHeight	= _screenHeight;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	mWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenWidth + 200, mScreenHeight, SDL_WINDOW_OPENGL);
	if (mWindow == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xff);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)){
		std::cout << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}
//==================================================================================================
//	Graphics::LoadTexture
//--------------------------------------------------------------------------------------------------
SDL_Texture *Graphics::LoadTexture(std::string const &path)
{
	SDL_Texture *tex	= nullptr;
	SDL_Surface *surf	= nullptr;

	surf = IMG_Load(path.c_str());
	if (surf == nullptr)
	{
		std::cout << IMG_GetError() << std::endl;
		return tex;
	}
	tex = SDL_CreateTextureFromSurface(mRenderer, surf);
	if (tex == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return tex;
	}
	SDL_FreeSurface(surf);
	return tex;
}
//==================================================================================================
//	Graphics::CreateTTF
//--------------------------------------------------------------------------------------------------
SDL_Texture *Graphics::CreateTTF(TTF_Font* font, std::string text, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *surf 		= nullptr;
	SDL_Texture *texture 	= nullptr;
	SDL_Color	color{r, g, b, 0};

	surf = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surf == nullptr)
	{
		std::cout << TTF_GetError() << std::endl;
		return nullptr;
	}
	texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	if (texture == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return texture;
	}
	SDL_FreeSurface(surf);
	return texture;
}

void Graphics::ClearBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture *tex, SDL_Rect *clip ,SDL_Rect *rend)
{
	//SDL_RenderCopyEx(mRenderer, tex, clip, rend, 0, NULL, flip);
	SDL_RenderCopy(mRenderer, tex, clip, rend);
}

void Graphics::Render()
{	
	SDL_RenderPresent(mRenderer);
}

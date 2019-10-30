#include "../include/InputManager.hpp"

InputManager* InputManager::sInstance = nullptr;

//**************************************************************************************************
//	InputManager::Instance
//--------------------------------------------------------------------------------------------------
InputManager *InputManager::Instance()
{
	if(sInstance == nullptr)
	{
		sInstance = new InputManager();
	}
	return (sInstance);
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

InputManager::InputManager()
{
	mKeybordState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeybordState = new Uint8[mKeyLength];
	memcpy(mPrevKeybordState, mKeybordState, mKeyLength);
}

InputManager::~InputManager()
{
	delete[] mPrevKeybordState;
	mPrevKeybordState = nullptr;
}

bool InputManager::KeyDown(int8_t scancode)
{
	return (mKeybordState[scancode] != 0);
}

bool InputManager::KeyPressed(int8_t scancode)
{
	return (mPrevKeybordState[scancode]) == 0 && (mKeybordState[scancode] != 0);
}

bool InputManager::KeyRealeased(SDL_Scancode scancode)
{
	return (mPrevKeybordState[scancode]) != 0 && (mKeybordState[scancode] == 0);
}

//============================================================
//	MousePos
//------------------------------------------------------------
// Vector2 InputManager::MousePos() const
// {
// 	return mMousePosition;
// }
//============================================================
//	MousePos
//------------------------------------------------------------
// void InputManager::MousePos(float _x, float _y)
// {
// 	mMousePosition.x = _x;
// 	mMousePosition.y = _y;
// }
//============================================================
//	MouseButtonDown
//------------------------------------------------------------
// bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
// {
// 	Uint32 mask = 0;

// 	switch(button)
// 	{
// 	case left:
// 		mask = SDL_BUTTON_LMASK;
// 		break;
// 	case right:
// 		mask = SDL_BUTTON_RMASK;
// 		break;
// 	case middle:
// 		mask = SDL_BUTTON_MMASK;
// 		break;
// 	case back:
// 		mask = SDL_BUTTON_X1MASK;
// 		break;
// 	case forward:
// 		mask = SDL_BUTTON_X2MASK;
// 		break;
// 	}
// 	return (mMouseState & mask);
// }
//============================================================
//	MouseButtonPressed
//------------------------------------------------------------
// bool InputManager::MouseButtonPressed(MOUSE_BUTTON button)
// {
// 	Uint32 mask = 0;

// 	switch(button)
// 	{
// 	case left:
// 		mask = SDL_BUTTON_LMASK;
// 		break;
// 	case right:
// 		mask = SDL_BUTTON_RMASK;
// 		break;
// 	case middle:
// 		mask = SDL_BUTTON_MMASK;
// 		break;
// 	case back:
// 		mask = SDL_BUTTON_X1MASK;
// 		break;
// 	case forward:
// 		mask = SDL_BUTTON_X2MASK;
// 		break;
// 	}
// 	return !(mPrevMouseState & mask) && (mMouseState & mask);
// }
//============================================================
//	MouseButtonRealesed
//------------------------------------------------------------
// bool InputManager::MouseButtonRealesed(MOUSE_BUTTON button)
// {
// 	Uint32 mask = 0;

// 	switch(button)
// 	{
// 	case left:
// 		mask = SDL_BUTTON_LMASK;
// 		break;
// 	case right:
// 		mask = SDL_BUTTON_RMASK;
// 		break;
// 	case middle:
// 		mask = SDL_BUTTON_MMASK;
// 		break;
// 	case back:
// 		mask = SDL_BUTTON_X1MASK;
// 		break;
// 	case forward:
// 		mask = SDL_BUTTON_X2MASK;
// 		break;
// 	}
// 	return (mPrevMouseState & mask) && !(mMouseState & mask);
// }

void InputManager::Update()
{
	// int x = static_cast<int>(mMousePosition.x);
	// int y = static_cast<int>(mMousePosition.y);
	// mMouseState = SDL_GetMouseState(&x, &y);
	// mMousePosition.x = static_cast<float>(x);
	// mMousePosition.y = static_cast<float>(y);
}

void InputManager::UpdatePrevInput()
{
	memcpy(mPrevKeybordState, mKeybordState, mKeyLength);
	//mPrevMouseState = mMouseState;
}
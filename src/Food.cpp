#include "Food.hpp"
#include <random>
#include <ctime>
#include <iostream>

//=================================================================================================
//	Food
//-------------------------------------------------------------------------------------------------
Food::Food(Vector2 _position, int32_t _width, int32_t _heigh)
: eInherited(static_cast<float>(_width / 2), FOOD)
{
	foodValue		= 10;
	mWidth			= _width;
	mHeight			= _heigh;
	mPos			= _position;
}
//=================================================================================================
// SetRespawnDementions
//-------------------------------------------------------------------------------------------------
void Food::SetRespawnDementions(int32_t _width, int32_t _height, const std::vector<std::string> map)
{
	while (mWidth < _width - TEXTURE_SIZE * 2)
	{
		mWidth += TEXTURE_SIZE;
	}
	while (mHeight < _height - TEXTURE_SIZE * 2)
	{
		mHeight += TEXTURE_SIZE;
	}
	mWidth /= TEXTURE_SIZE;
	mHeight /= TEXTURE_SIZE;
	levelMap = map;
}
//=================================================================================================
// ReSpawn
//-------------------------------------------------------------------------------------------------
void Food::ReSpawn()
{
	srand(time(0));
	int32_t x;
	int32_t y;
	char tile;
	while(1)
	{
		x = TEXTURE_SIZE + TEXTURE_SIZE * (rand() % mWidth);
		y = TEXTURE_SIZE + TEXTURE_SIZE * (rand() % mHeight);
		tile = levelMap[y / TEXTURE_SIZE][x / TEXTURE_SIZE];
		if (tile == '.')
		{
			break;
		}
	}

	Position(Vector2(static_cast<float>(x), static_cast<float>(y)));
}
//=================================================================================================
// FoodValue
//-------------------------------------------------------------------------------------------------
int32_t Food::FoodValue() const
{
	return foodValue;
}
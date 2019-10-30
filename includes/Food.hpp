#ifndef FOOD_HPP
#define FOOD_HPP

#include "Collider.hpp"

// $todo: make a diffent type of food. inherit from foodBase class (maybe)

//**************************************************************************************************
//	Food
//--------------------------------------------------------------------------------------------------
class Food : public Collider
{
	using eInherited = Collider;
public:
	Food(Vector2 position, int32_t _width, int32_t _heigh);
	Food(const Food&)						= default;
	virtual ~Food() 						= default;

	Food&			operator=(const Food&)	= default;
	
	void			SetRespawnDementions(int32_t width, int32_t height, const std::vector<std::string> map);
	int32_t			FoodValue() const;

	void			ReSpawn();

protected:
	int32_t						foodValue;
	int32_t						mWidth; // size for food respawn depends on map
	int32_t						mHeight; // size for food respawn depends on map
	std::vector<std::string> 	levelMap;
};

#endif

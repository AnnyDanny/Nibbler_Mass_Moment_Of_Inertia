#ifndef WALL_HPP
#define WALL_HPP

#include "Collider.hpp"

//**************************************************************************************************
//	Wall
//--------------------------------------------------------------------------------------------------
class Wall : public Collider
{
	using eInherited = Collider;
public:
	Wall(Vector2 position, int32_t _x, int32_t _y, int32_t _width, int32_t _heigh);
	Wall(const Wall&)						= default;
	virtual	~Wall()							= default;

	Wall&			operator=(const Wall&)	= default;
	void			Update();

protected:

};

#endif
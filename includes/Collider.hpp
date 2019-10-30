#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "MathHelper.hpp"
#include <vector>
#include <memory>

//=================================================================================================
//	for this project it will be only Circle-Circle collision, so we do not need enum with
//	other collider types, only a CollideType to interact with different entities
//-------------------------------------------------------------------------------------------------
class Collider
{
public:
	enum	CollideType
	{
		PLAYER	= 1,
		FOOD	= 2,
		WALL	= 3,

		UNKNOWN	= -1
	};
public:
	enum : int32_t 
	{
		TEXTURE_SIZE = 32,
	};
public:
	Collider(float radius, CollideType type = UNKNOWN);
	Collider(const Collider&)					= default;
	virtual	~Collider()							= default;

	Collider&		operator=(const Collider&)	= default;

	void			Position(Vector2 pos);
	Vector2			Position()			const;
	float			Radius()			const;
	CollideType		GetCollideType()	const;
	bool			CheckCircleCollision(const Collider&, const Collider&);
	bool			CheckCircleCollision(const Vector2&, const Vector2&, float firstEntityRadius, float secondEntityRadius);
	bool  			CheckCircleCollision(const Collider&, const Vector2&, float secondEntityRadius);
	
protected:
	Vector2			mPos;
	Vector2			mDir;
	float			mRadius;
	CollideType		mColliderType;
};

#endif

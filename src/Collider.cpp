#include "Collider.hpp"
#include <iostream>

//=================================================================================================
//	Collider
//-------------------------------------------------------------------------------------------------
Collider::Collider(float _radius, CollideType _type)
: mRadius(_radius)
, mColliderType(_type)
{
	mDir = VEC2_ZERO;
}
//=================================================================================================
//	Position
//-------------------------------------------------------------------------------------------------
void Collider::Position(Vector2 _pos)
{
	mPos = _pos;
}
//=================================================================================================
//	Position
//-------------------------------------------------------------------------------------------------
Vector2 Collider::Position() const
{
	return mPos;
}
//=================================================================================================
//	Radius
//-------------------------------------------------------------------------------------------------
float Collider::Radius() const
{
	return mRadius;
}
//=================================================================================================
//	GetCollideType
//-------------------------------------------------------------------------------------------------
Collider::CollideType Collider::GetCollideType() const
{
	return mColliderType;
}
//=================================================================================================
// CheckCircleCollision
//-------------------------------------------------------------------------------------------------
bool Collider::CheckCircleCollision(const Collider& _ent1, const Collider& _ent2)
{
	return (_ent1.Position() - _ent2.Position()).Magnitude() < (_ent1.Radius() + _ent2.Radius());
}
//=================================================================================================
// CheckCircleCollision
//-------------------------------------------------------------------------------------------------
bool Collider::CheckCircleCollision(const Vector2& _vec1, const Vector2& _vec2, float _firstEntityRadius, float _secondEntityRadius)
{
	return (_vec1 - _vec2).Magnitude() < (_firstEntityRadius + _secondEntityRadius);
}

bool Collider::CheckCircleCollision(const Collider& _ent1, const Vector2& _vec2, float _secondEntityRadius)
{
 return (_ent1.Position() - _vec2).Magnitude() < (_ent1.Radius() + _secondEntityRadius);
}
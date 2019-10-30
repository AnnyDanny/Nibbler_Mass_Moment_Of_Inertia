#ifndef _PLAYER_HPP_
#define	_PLAYER_HPP_

#include "Collider.hpp"
#include <iostream>
#include <vector>

//**************************************************************************************************
//	Player
//--------------------------------------------------------------------------------------------------
class Player : public Collider
{
	using eInherited = Collider;
public:
	Player();
	Player(const Player&)						= default;
	virtual ~Player()							= default;

	Player&			operator=(const Player&)	= default;

	void			Init(const Vector2& pos, const Vector2& direction = UP_DIR);
	void			Update();

	bool			IsAlive()	const;
	void			IsAlive(bool isAlive);
	bool			IsDead()	const;
	void			IsDead(bool isDead);
	int32_t			Score()		const;
	void			Translate(Vector2 amount);
	void			Collide(Collider&, int32_t foodValue);
	
	Vector2			HeadPos() const; // consider [0] is always head position
	Vector2			HeadDir() const;
	void			HeadDir(Vector2 pos);

	const std::vector<Vector2>&		PlayerPos();
	const std::vector<Vector2I>&	TexturePos();
	void							RotateHead(int32_t x, int32_t y);

protected:
	void			CollideWithSelf();
	void			CollideWithWall();
	void			CollideWithFood(int32_t foodValue);

	void			ChangeDirectionBody(const Vector2&, const Vector2& previousDirection, size_t pos);
	void			ChangeDirectionTail(const Vector2&);
	void			BodyGrow();

	bool					isAlive;
	bool					isDead;
	int32_t					score;
	std::vector<Vector2>	mPlayerPos;
	std::vector<Vector2>	mPlayerDir;
	std::vector<Vector2I>	mPlayerStartTextPos;
};

#endif 

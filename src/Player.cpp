#include "Player.hpp"

//=================================================================================================
//	Player
//-------------------------------------------------------------------------------------------------
Player::Player()
: eInherited(Collider::TEXTURE_SIZE / 2, PLAYER)
{
	isAlive		= true;
	isDead		= false;
	score		= 0;
	mPos 		= Vector2(0.0f, 0.0f);
}
//=================================================================================================
//	Init
//-------------------------------------------------------------------------------------------------
void Player::Init(const Vector2& pos, const Vector2& direction)
{
	mPlayerPos.push_back(pos);
	mPlayerStartTextPos.push_back(Vector2I(0, 0));
	mPlayerDir.push_back(direction);
	mPos = mPlayerPos.front();
	mPlayerStartTextPos.front() = Vector2I(96, 0);
}
//=================================================================================================
//	RotateHead
//-------------------------------------------------------------------------------------------------
void Player::RotateHead(int32_t _x, int32_t _y)
{
	mPlayerStartTextPos[0] = { _x, _y };
}
//=================================================================================================
// Update
//-------------------------------------------------------------------------------------------------
void Player::Update()
{
	mPos = mPlayerPos.front();
	Translate(mPlayerDir.front());
	CollideWithSelf();
}
//=================================================================================================
// Collide
//-------------------------------------------------------------------------------------------------
void Player::Collide(Collider& _toCollideWith, int32_t foodValue)
{
	switch(_toCollideWith.GetCollideType())
	{
	case WALL:		CollideWithWall();	break;
	case FOOD:		CollideWithFood(foodValue);	break;
	case PLAYER:	CollideWithSelf();	break;
	default:		break;
	}
}
//=================================================================================================
// HeadPos
//-------------------------------------------------------------------------------------------------
Vector2 Player::HeadPos() const
{
	return mPlayerPos[0];
}
//=================================================================================================
// HeadDir
//-------------------------------------------------------------------------------------------------
Vector2 Player::HeadDir() const
{
	return mPlayerDir[0];
}
//=================================================================================================
// HeadDir
//-------------------------------------------------------------------------------------------------
void Player::HeadDir(Vector2 pos)
{
	mPlayerDir[0] = pos;
}
//=================================================================================================
// PlayerPos
//-------------------------------------------------------------------------------------------------
const std::vector<Vector2>& Player::PlayerPos()
{
	return mPlayerPos;
}
//=================================================================================================
// TexturePos
//-------------------------------------------------------------------------------------------------
const std::vector<Vector2I>& Player::TexturePos()
{
	return mPlayerStartTextPos;
}
//=================================================================================================
// CollideWithWall
//-------------------------------------------------------------------------------------------------
void Player::CollideWithWall()
{
	isAlive	= false;
}
//=================================================================================================
// CollideWithFood
//-------------------------------------------------------------------------------------------------
void Player::CollideWithFood(int32_t foodValue)
{
	score += foodValue;
	BodyGrow();
}
//=================================================================================================
// CollideWithSelf
//-------------------------------------------------------------------------------------------------
void Player::CollideWithSelf()
{
	for (size_t i = 1; i < mPlayerPos.size(); ++i)
	{
		if (CheckCircleCollision(mPlayerPos.front(), mPlayerPos[i], 16.0f, 16.0f))
		{
			isAlive = false;
		}
	}
}
//=================================================================================================
// IsAlive
//-------------------------------------------------------------------------------------------------
bool Player::IsAlive() const
{
	return isAlive;
}
//=================================================================================================
// IsAlive
//-------------------------------------------------------------------------------------------------
void Player::IsAlive(bool _isAlive)
{
	isAlive = _isAlive;
}
//=================================================================================================
// IsDead
//-------------------------------------------------------------------------------------------------
bool Player::IsDead() const
{
	return isDead;
}
void Player::IsDead(bool _isDead)
{
	isDead = _isDead;
	for(std::size_t i = 0; i < mPlayerPos.size(); ++i)
	{
		mPlayerPos[i].x = -32.0f;
		mPlayerPos[i].y = -32.0f;
	}
}
//=================================================================================================
// Score
//-------------------------------------------------------------------------------------------------
int32_t Player::Score() const
{
	return score;
}
//=================================================================================================
// BodyGrow
//-------------------------------------------------------------------------------------------------
void Player::BodyGrow()
{
	Vector2I tmpCoords = mPlayerStartTextPos.back();
	mPlayerStartTextPos.push_back(tmpCoords);
	
	mPlayerPos.push_back(mPlayerPos.back());
	mPlayerDir.push_back(mPlayerDir.back());
}
//=================================================================================================
// Translate
//-------------------------------------------------------------------------------------------------
void Player::Translate(Vector2 _amount)
{
	Vector2 prevHeadPos				= mPlayerPos[0];
	Vector2 currentHeadDirection	= mPlayerDir[0]; // current
	Vector2 prevBodyPos;
	Vector2 prevBodyDir;

	mPos += _amount;
	mPlayerPos[0] += mPlayerDir[0];
	for(size_t i = 1; i < mPlayerPos.size() - 1; ++i)
	{
		prevBodyPos		= mPlayerPos[i];
		prevBodyDir		= mPlayerDir[i];
		mPlayerPos[i] = (prevHeadPos);
		mPlayerDir[i] = (currentHeadDirection);
		ChangeDirectionBody(mPlayerDir[i], prevBodyDir, i);
		prevHeadPos				= prevBodyPos;
		currentHeadDirection	= prevBodyDir;
	}
	mPlayerPos.back()			= prevHeadPos;
	mPlayerDir.back()			= currentHeadDirection;
	ChangeDirectionTail(mPlayerDir.back());
}
//=================================================================================================
// ChangeDirectionBody
//-------------------------------------------------------------------------------------------------
void Player::ChangeDirectionBody(const Vector2& _body, const Vector2& _previousDirection, size_t pos)
{
	if (_body == _previousDirection)
	{
		// if direction isn't changed next frame, set texture due to direction
		if (_body == RIGHT_DIR || _body == LEFT_DIR)
		{
			mPlayerStartTextPos[pos] = { 32, 0 };
		}
		else
		{
			mPlayerStartTextPos[pos] = { 64, 32 };
		}
	}
	else
	{
		// direction changed
		if (_previousDirection == UP_DIR)
		{
			if (_body == RIGHT_DIR)
			{
				mPlayerStartTextPos[pos] = { 0, 0 };
			}
			else
			{
				mPlayerStartTextPos[pos] = { 64, 0 };
			}
		}
		else if (_previousDirection == DOWN_DIR)
		{
			if (_body == RIGHT_DIR)
			{
				mPlayerStartTextPos[pos] = { 0, 32 };
			}
			else
			{
				mPlayerStartTextPos[pos] = { 64, 64 };
			}
		}
		else if (_previousDirection == RIGHT_DIR)
		{
			if (_body == UP_DIR)
			{
				mPlayerStartTextPos[pos] = { 64, 64 };
			}
			else
			{
				mPlayerStartTextPos[pos] = { 64, 0 };
			}
		}
		else if (_previousDirection == LEFT_DIR)
		{
			if (_body == UP_DIR)
			{
				mPlayerStartTextPos[pos] = { 0, 32 };
			}
			else
			{
				mPlayerStartTextPos[pos] = { 0, 0 };
			}
		}
	}
}
//==================================================================================================
//	Player::ChangeDirectionTail
//--------------------------------------------------------------------------------------------------
void Player::ChangeDirectionTail(const Vector2& _tail)
{
	if(_tail == RIGHT_DIR)
	{
		mPlayerStartTextPos.back() = { 128, 64 };
	}
	else if(_tail == LEFT_DIR)
	{
		mPlayerStartTextPos.back() = { 96, 96 };
	}
	else if(_tail == UP_DIR)
	{
		mPlayerStartTextPos.back() = { 96, 64 };
	}
	else if(_tail == DOWN_DIR)
	{
		mPlayerStartTextPos.back() = { 128, 96 };
	}
}

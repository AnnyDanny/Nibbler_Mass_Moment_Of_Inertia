#ifndef _MATHHELPER_HPP
#define _MATHHELPER_HPP
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

struct Vector2I
{
	Vector2I(int _x = 0, int _y = 0) : x(_x), y(_y) {}

	int	x;
	int	y;
};

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		:x(_x), y(_y) {}
	
	float MagnnitudeSqr()
	{
		return x * x + y * y;
	}

	float Magnitude()
	{
		return (float)sqrt(x * x + y * y);
	}

	Vector2 Normalized()
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2 &operator +=(const Vector2 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 &operator -=(const Vector2 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool operator ==(const Vector2 &rhs)
	{
		return	static_cast<int>(x)		== static_cast<int>(rhs.x)
				&& static_cast<int>(y)	== static_cast<int>(rhs.y);
	}
	bool operator ==(const Vector2& rhs) const
	{
		return	static_cast<int>(x)		== static_cast<int>(rhs.x)
				&& static_cast<int>(y)	== static_cast<int>(rhs.y);
	}
	bool operator !=(const Vector2& rhs)
	{
		return !operator==(rhs);
	}
	bool operator !=(const Vector2& rhs) const
	{
		return !operator==(rhs);
	}
};

inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator*(const Vector2 &lhs, const float &rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 RotateVector(Vector2 &vec, float angle)
{
	float radAngle = static_cast<float>(angle * DEG_TO_RAD);
	return Vector2(static_cast<float>(vec.x * cos(radAngle) - vec.y * sin(radAngle)), static_cast<float>(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

const Vector2 RIGHT_DIR	= {32.0f, 0.0f};
const Vector2 LEFT_DIR	= {-32.0f, 0.0f};
const Vector2 UP_DIR	= {0.0f, -32.0f};
const Vector2 DOWN_DIR	= {0.0f, 32.0f};
const Vector2 VEC2_ZERO	= {0.0f, 0.0f};

#endif
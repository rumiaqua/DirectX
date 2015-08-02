# include "Vector2.hpp"

# include "Math/Math.hpp"

# include "Vector3/Vector3.hpp"

namespace aqua
{
	const Vector2 Vector2::Zero { 0.0f, 0.0f };

	const Vector2 Vector2::One { 1.0f, 1.0f };

	const Vector2 Vector2::Left { -1.0f, 0.0f };

	const Vector2 Vector2::Right { 1.0f,0.0f };

	const Vector2 Vector2::Up { 0.0f,-1.0f };

	const Vector2 Vector2::Down { 0.0f, 1.0f };

	Vector2::Vector2()
		: Vector2(0.0f, 0.0f)
	{

	}

	Vector2::Vector2(const Vector2& other)
		: Vector2(other.x, other.y)
	{

	}

	Vector2::Vector2(const XMVECTOR& xm)
		: Vector2(xm.vector4_f32[0], xm.vector4_f32[1])
	{

	}

	Vector2::Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2& Vector2::operator = (const Vector2& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	float Vector2::LengthSquared(const Vector2& v)
	{
		return Dot(v, v);
	}

	float Vector2::Length(const Vector2& v)
	{
		return Math::Sqrt(LengthSquared(v));
	}

	Vector2 Vector2::Normalize(const Vector2& v)
	{
		float lengthSquared = LengthSquared(v);
		if (lengthSquared == 0.0f)
		{
			return v;
		}
		return v / Math::Sqrt(lengthSquared);
	}

	Vector2 Vector2::Saturate(const Vector2& v)
	{
		return Vector2(
			Math::Saturate(v.x),
			Math::Saturate(v.y));
	}

	Vector2 Vector2::Smooth(const Vector2& v, int f)
	{
		return Vector2(
			Math::Smooth(v.x, f),
			Math::Smooth(v.y, f));
	}

	float Vector2::Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	float Vector2::Cross(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v2.y * v2.x;
	}

	float Vector2::Distance(const Vector2& v1, const Vector2& v2)
	{
		return Length(v2 - v1);
	}

	Vector2 Vector2::Lerp(const Vector2& v1, const Vector2& v2, float t)
	{
		return v1 + (v2 - v1) * t;
	}

	bool operator == (const Vector2& v1, const Vector2& v2)
	{
		return
			v1.x == v2.x &&
			v1.y == v2.y;
	}

	bool operator != (const Vector2& v1, const Vector2& v2)
	{
		return !(v1 == v2);
	}

	Vector2 operator + (const Vector2& v)
	{
		return v;
	}
	Vector2 operator - (const Vector2& v)
	{
		return v * -1.0f;
	}
	Vector2& operator += (Vector2& v1, const Vector2& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	Vector2& operator -= (Vector2& v1, const Vector2& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	Vector2& operator *= (Vector2& v, float s)
	{
		v.x *= s;
		v.y *= s;
		return v;
	}

	Vector2& operator *= (float s, Vector2& v)
	{
		return v *= s;
	}
	Vector2& operator /= (Vector2& v, float s)
	{
		v.x /= s;
		v.y /= s;
		return v;
	}
	Vector2 operator + (const Vector2& v1, const Vector2& v2)
	{
		Vector2 result = v1;
		return result += v2;
	}
	Vector2 operator - (const Vector2& v1, const Vector2& v2)
	{
		Vector2 result = v1;
		return result -= v2;
	}
	Vector2 operator * (const Vector2& v, float s)
	{
		Vector2 result = v;
		return result *= s;
	}
	Vector2 operator * (float s, const Vector2& v)
	{
		return v * s;
	}
	Vector2 operator / (const Vector2& v, float s)
	{
		Vector2 result = v;
		return result /= s;
	}
}

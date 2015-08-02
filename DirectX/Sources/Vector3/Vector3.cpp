# include "Vector3.hpp"

# include "Math/Math.hpp"

# include "Vector2/Vector2.hpp"

# include "Vector4/Vector4.hpp"

namespace aqua
{
	using namespace DirectX;

	const Vector3 Vector3::Zero { 0.0f, 0.0f, 0.0f };

	const Vector3 Vector3::One { 1.0f, 1.0f, 1.0f };

	const Vector3 Vector3::Left { -1.0f, 0.0f, 0.0f };

	const Vector3 Vector3::Right { 1.0f,0.0f,0.0f };

	const Vector3 Vector3::Up { 0.0f, 1.0f, 0.0f };

	const Vector3 Vector3::Down { 0.0f, -1.0f, 0.0f };

	const Vector3 Vector3::Forward { 0.0f, 0.0f, 1.0f };

	const Vector3 Vector3::Backward { 0.0f, 0.0f, -1.0f };

	Vector3::Vector3()
		: Vector3(0.0f, 0.0f, 0.0f)
	{

	}

	Vector3::Vector3(const Vector3& other)
		: Vector3(other.x, other.y, other.z)
	{

	}

	Vector3::Vector3(const DirectX::XMVECTOR& xm)
		: Vector3(xm.vector4_f32[0], xm.vector4_f32[1], xm.vector4_f32[2])
	{

	}

	Vector3::Vector3(const Vector2& v, float z)
		: Vector3(v.x, v.y, z)
	{

	}

	Vector3::Vector3(const Vector4& v)
		: Vector3(v.x, v.y, v.z)
	{

	}

	Vector3::Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{

	}

	Vector3& Vector3::operator = (const Vector3& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	float Vector3::LengthSquared(const Vector3& v)
	{
		return Dot(v, v);
	}

	float Vector3::Length(const Vector3& v)
	{
		return Math::Sqrt(LengthSquared(v));
	}

	Vector3 Vector3::Normalize(const Vector3& v)
	{
		auto lengthSquared = LengthSquared(v);

		if (lengthSquared == 0.0f)
		{
			return v;
		}

		auto result = v;

		return result /= Math::Sqrt(lengthSquared);
	}

	Vector3 Vector3::Saturate(const Vector3& v)
	{
		return Vector3(
			Math::Saturate(v.x),
			Math::Saturate(v.y),
			Math::Saturate(v.z));
	}

	Vector3 Vector3::Smooth(const Vector3 & v, int f)
	{
		return Vector3(
			Math::Smooth(v.x, f),
			Math::Smooth(v.y, f),
			Math::Smooth(v.z, f));
	}

	float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	XMVECTOR Vector3::ToVector(const Vector3& v, float w)
	{
		return XMVectorSet(v.x, v.y, v.z, w);
	}

	float Vector3::Distance(const Vector3& v1, const Vector3& v2)
	{
		return Length(v2 - v1);
	}

	Vector3 Vector3::Scratch(const Vector3& v, const Vector3& normal)
	{
		Vector3 n = Normalize(normal);
		return v - n * Dot(v, n);
	}

	Vector3 Vector3::Reflect(const Vector3& v, const Vector3& normal)
	{
		Vector3 n = Normalize(normal);
		return v - n * Dot(v, n) * 2.0f;
	}

	Vector3 Vector3::Projection(const Vector3& v, const Vector3& target)
	{
		Vector3 n = Normalize(target);
		return n * Dot(v, n);
	}

	Vector3 Vector3::Lerp(const Vector3& v1, const Vector3& v2, float t)
	{
		return v1 + (v2 - v1) * t;
	}

	bool operator == (const Vector3& v1, const Vector3& v2)
	{
		return
			v1.x == v2.x &&
			v1.y == v2.y &&
			v1.z == v2.z;
	}

	bool operator != (const Vector3& v1, const Vector3& v2)
	{
		return !(v1 == v2);
	}

	Vector3 operator + (const Vector3& v)
	{
		return v;
	}

	Vector3 operator - (const Vector3& v)
	{
		return v * -1.0f;
	}

	Vector3& operator += (Vector3& v1, const Vector3& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		return v1;
	}

	Vector3& operator -= (Vector3& v1, const Vector3& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		return v1;
	}

	Vector3& operator *= (Vector3& v, float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		return v;
	}

	Vector3& operator *= (float s, Vector3& v)
	{
		return v *= s;
	}

	Vector3& operator /= (Vector3& v, float s)
	{
		v.x /= s;
		v.y /= s;
		v.z /= s;
		return v;
	}

	Vector3 operator + (const Vector3& v1, const Vector3& v2)
	{
		auto result = v1;
		return result += v2;
	}

	Vector3 operator - (const Vector3& v1, const Vector3& v2)
	{
		auto result = v1;
		return result -= v2;
	}

	Vector3 operator * (const Vector3& v, float s)
	{
		auto result = v;
		return result *= s;
	}

	Vector3 operator * (float s, const Vector3& v)
	{
		return v * s;
	}

	Vector3 operator / (const Vector3& v, float s)
	{
		auto result = v;
		return result /= s;
	}
}

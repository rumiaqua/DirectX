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

	float Vector3::LengthSquared() const
	{
		return Dot(*this);
	}

	float Vector3::Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	Vector3 Vector3::Normalized() const
	{
		Vector3 result = *this;
		return result.Normalize();
	}

	Vector3 Vector3::Saturated() const
	{
		Vector3 v = *this;
		return v.Saturate();
	}

	Vector3 Vector3::Smoothed(int f) const
	{
		Vector3 v = *this;
		return v.Smooth(f);
	}

	float Vector3::Dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3 Vector3::Cross(const Vector3& v) const
	{
		return Vector3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}

	XMVECTOR Vector3::ToVector(float w) const
	{
		return XMVectorSet(x, y, z, w);
	}

	float Vector3::Distance(const Vector3& v) const
	{
		return (v - *this).Length();
	}

	Vector3 Vector3::Scratched(const Vector3& normal) const
	{
		Vector3 v = *this;
		return v.Scratch(normal);
	}

	Vector3 Vector3::Reflected(const Vector3& normal) const
	{
		Vector3 v = *this;
		return v.Reflect(normal);
	}

	Vector3 Vector3::Projected(const Vector3& target) const
	{
		Vector3 v = *this;
		return v.Project(target);
	}

	Vector3& Vector3::Normalize()
	{
		float lengthSquared = LengthSquared();

		if (lengthSquared == 0.0f)
		{
			return *this;
		}

		return *this /= Math::Sqrt(lengthSquared);
	}

	Vector3& Vector3::Saturate()
	{
		x = Math::Saturate(x);
		y = Math::Saturate(y);
		z = Math::Saturate(z);
		return *this;
	}

	Vector3& Vector3::Smooth(int f)
	{
		x = Math::Smooth(x, f);
		y = Math::Smooth(y, f);
		z = Math::Smooth(z, f);
		return *this;
	}

	Vector3 & Vector3::Scratch(const Vector3 & normal)
	{
		Vector3 n = normal.Normalized();
		return *this -= n * Dot(n);
	}

	Vector3 & Vector3::Reflect(const Vector3 & normal)
	{
		Vector3 n = normal.Normalized();
		return *this -= n * Dot(n) * 2.0f;
	}

	Vector3 & Vector3::Project(const Vector3 & target)
	{
		Vector3 n = target.Normalized();
		return *this *= Dot(n);
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
		Vector3 result = v1;
		return result += v2;
	}

	Vector3 operator - (const Vector3& v1, const Vector3& v2)
	{
		Vector3 result = v1;
		return result -= v2;
	}

	Vector3 operator * (const Vector3& v, float s)
	{
		Vector3 result = v;
		return result *= s;
	}

	Vector3 operator * (float s, const Vector3& v)
	{
		return v * s;
	}

	Vector3 operator / (const Vector3& v, float s)
	{
		Vector3 result = v;
		return result /= s;
	}
}

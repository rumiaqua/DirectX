# include "Vector4.hpp"

# include "Math/Math.hpp"

# include "Vector2/Vector2.hpp"

# include "Vector3/Vector3.hpp"

namespace aqua
{
	const Vector4 Vector4::Zero { 0.0f, 0.0f, 0.0f, 0.0f };

	const Vector4 Vector4::One { 1.0f, 1.0f, 1.0f, 1.0f };

	Vector4::Vector4()
		: Vector4(0.0f, 0.0f, 0.0f, 0.0f)
	{

	}

	Vector4::Vector4(const Vector4& other)
		: Vector4(other.x, other.y, other.z, other.w)
	{

	}

	Vector4::Vector4(const Vector3& v, float w)
		: Vector4(v.x, v.y, v.z, w)
	{

	}

	Vector4::Vector4(const XMVECTOR& xm)
		: Vector4(xm.vector4_f32[0], xm.vector4_f32[1], xm.vector4_f32[2], xm.vector4_f32[3])
	{

	}

	Vector4::Vector4(const Vector2& v1, const Vector2& v2)
		: Vector4(v1.x, v1.y, v2.x, v2.y)
	{

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{

	}

	Vector4& Vector4::operator = (const Vector4& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
		return *this;
	}

	Vector4::operator XMVECTOR()
	{
		return xm;
	}

	Vector4::operator const XMVECTOR() const
	{
		return xm;
	}

	Vector4::operator float* ()
	{
		return elm;
	}

	Vector4::operator const float* () const
	{
		return elm;
	}

	XMVECTOR* Vector4::operator & ()
	{
		return &xm;
	}

	const XMVECTOR* Vector4::operator & () const
	{
		return &xm;
	}

	float Vector4::LengthSquared(const Vector4& v)
	{
		return Dot(v, v);
	}

	float Vector4::Length(const Vector4& v)
	{
		return Math::Sqrt(LengthSquared(v));
	}

	Vector4 Vector4::Normalize(const Vector4& v)
	{
		auto lengthSquared = LengthSquared(v);

		if (lengthSquared == 0.0f)
		{
			return v;
		}

		auto result = v;

		return result /= Math::Sqrt(lengthSquared);
	}

	Vector4 Vector4::Saturate(const Vector4& v)
	{
		return Vector4(
			Math::Saturate(v.x),
			Math::Saturate(v.y),
			Math::Saturate(v.z),
			Math::Saturate(v.w));
	}

	Vector4 Vector4::Smooth(const Vector4 & v, int f)
	{
		return Vector4(
			Math::Smooth(v.x, f),
			Math::Smooth(v.y, f),
			Math::Smooth(v.z, f),
			Math::Smooth(v.w, f));
	}

	float Vector4::Dot(const Vector4& v1, const Vector4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	float Vector4::Distance(const Vector4& v1, const Vector4& v2)
	{
		return Length(v2 - v1);
	}

	Vector4 Vector4::Lerp(const Vector4& v1, const Vector4& v2, float t)
	{
		return v1 + (v2 - v1) * t;
	}

	bool operator == (const Vector4& v1, const Vector4& v2)
	{
		return
			v1.x == v2.x &&
			v1.y == v2.y &&
			v1.z == v2.z &&
			v1.w == v2.w;
	}

	bool operator != (const Vector4& v1, const Vector4& v2)
	{
		return !(v1 == v2);
	}

	Vector4 operator + (const Vector4& v)
	{
		return v;
	}

	Vector4 operator - (const Vector4& v)
	{
		return v * -1.0f;
	}

	Vector4& operator += (Vector4& v1, const Vector4& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		v1.w += v2.w;
		return v1;
	}

	Vector4& operator -= (Vector4& v1, const Vector4& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		v1.w -= v2.w;
		return v1;
	}

	Vector4& operator *= (Vector4& v, float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		v.w *= s;
		return v;
	}

	Vector4& operator *= (float s, Vector4& v)
	{
		return v *= s;
	}

	Vector4& operator /= (Vector4& v, float s)
	{
		v.x /= s;
		v.y /= s;
		v.z /= s;
		v.w /= s;
		return v;
	}

	Vector4 operator + (const Vector4& v1, const Vector4& v2)
	{
		auto result = v1;
		return result += v2;
	}

	Vector4 operator - (const Vector4& v1, const Vector4& v2)
	{
		auto result = v1;
		return result -= v2;
	}

	Vector4 operator * (const Vector4& v, float s)
	{
		auto result = v;
		return result *= s;
	}

	Vector4 operator * (float s, const Vector4& v)
	{
		return v * s;
	}

	Vector4 operator / (const Vector4& v, float s)
	{
		auto result = v;
		return result /= s;
	}
}

# include "Vector3.hpp"

Vector3::Vector3()
	: Vector3(0.0f, 0.0f, 0.0f)
{

}

Vector3::Vector3(const Vector3& other)
	: Vector3(other.x, other.y, other.z)
{

}

Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{

}

Vector3::Vector3(const Float3& f)
	: Vector3(f.x, f.y, f.z)
{

}

Vector3& Vector3::operator = (const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vector3::operator Float3() const
{
	return Float3(x, y, z);
}

float Vector3::LengthSquared(const Vector3& v)
{
	return Dot(v, v);
}

float Vector3::Length(const Vector3& v)
{
	return std::sqrtf(LengthSquared(v));
}

Vector3& Vector3::Normalize(Vector3& v)
{
	auto lengthSquared = LengthSquared(v);

	if (lengthSquared == 0.0f)
	{
		return v;
	}

	return v / std::sqrtf(lengthSquared);
}

Vector3 Vector3::Normalized(const Vector3& v)
{
	auto result = v;
	return Normalize(result);
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

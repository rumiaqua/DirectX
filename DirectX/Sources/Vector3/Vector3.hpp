# pragma once

class Vector3
{
	// constructor
public:

	Vector3();

	Vector3(const Vector3& other);

	Vector3(float x, float y, float z);

	Vector3(const Float3& f);

	// operator overload
public:

	Vector3& operator = (const Vector3& other);

	operator Float3() const;

	// unary math method
public:

	static float LengthSquared(const Vector3& v);

	static float Length(const Vector3& v);

	static Vector3& Normalize(Vector3& v);

	static Vector3 Normalized(const Vector3& v);

	// binary math method
public:

	static float Dot(const Vector3& v1, const Vector3& v2);

	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

public:

	float x;

	float y;

	float z;
};

bool operator == (const Vector3& v1, const Vector3& v2);

bool operator != (const Vector3& v1, const Vector3& v2);

Vector3& operator += (Vector3& v1, const Vector3& v2);

Vector3& operator -= (Vector3& v1, const Vector3& v2);

Vector3& operator *= (Vector3& v, float s);

Vector3& operator *= (float s, Vector3& v);

Vector3& operator /= (Vector3& v, float s);

Vector3 operator + (const Vector3& v1, const Vector3& v2);

Vector3 operator - (const Vector3& v1, const Vector3& v2);

Vector3 operator * (const Vector3& v, float s);

Vector3 operator * (float s, const Vector3& v);

Vector3 operator / (const Vector3& v, float s);

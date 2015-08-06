# include "Quaternion.hpp"

# include "Matrix/Matrix.hpp"

# include "Vector2/Vector2.hpp"

# include "Vector3/Vector3.hpp"

namespace aqua
{
	using namespace DirectX;

	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		xm = XMVectorSet(x, y, z, w);
	}

	Quaternion::Quaternion(const Vector3& axis, float angle)
	{
		xm = XMQuaternionRotationNormal(
			axis.ToVector(0.0f), angle);
	}

	Quaternion::Quaternion(const XMVECTOR& v)
	{
		xm = v;
	}

	// static

	Quaternion Quaternion::Identity()
	{
		return XMQuaternionIdentity();
	}

	Quaternion Quaternion::Roll(float angle)
	{
		return XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, angle);
	}

	Quaternion Quaternion::Pitch(float angle)
	{
		return XMQuaternionRotationRollPitchYaw(angle, 0.0f, 0.0f);
	}

	Quaternion Quaternion::Yaw(float angle)
	{
		return XMQuaternionRotationRollPitchYaw(0.0f, angle, 0.0f);
	}

	Quaternion Quaternion::RollPitchYaw(float roll, float pitch, float yaw)
	{
		return XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	}

	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		return XMQuaternionNormalize(q.xm);
	}

	Matrix Quaternion::ToMatrix(const Quaternion& q)
	{
		return XMMatrixRotationQuaternion(q.xm);
	}

	bool Quaternion::IsIdentity(const Quaternion& q)
	{
		return XMQuaternionIsIdentity(q.xm);
	}

	Quaternion operator * (const Quaternion& q, const Quaternion& p)
	{
		return XMQuaternionMultiply(q.xm, p.xm);
	}

	Quaternion& operator *= (Quaternion& q, const Quaternion& p)
	{
		q = q * p;
		return q;
	}

	Vector2 operator * (const Vector2& v, const Quaternion& q)
	{
		return v * Quaternion::ToMatrix(q);
	}

	Vector2 operator *= (Vector2& v, const Quaternion& q)
	{
		v = v * q;
		return v;
	}

	Vector3 operator * (const Vector3& v, const Quaternion& q)
	{
		return v * Quaternion::ToMatrix(q);
	}

	Vector3 operator *= (Vector3& v, const Quaternion& q)
	{
		v = v * q;
		return v;
	}
}

# include "Matrix.hpp"

# include "Quaternion/Quaternion.hpp"

# include "Vector2/Vector2.hpp"

# include "Vector3/Vector3.hpp"

# include "Vector4/Vector4.hpp"

namespace aqua
{
	using namespace DirectX;

	Matrix::Matrix(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44)
		: XMMATRIX(
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44)
	{

	}

	Matrix::Matrix(const XMMATRIX& matrix)
		: XMMATRIX(matrix)
	{

	}

	Matrix::operator const float*() const
	{
		return &m[0][0];
	}

	Matrix Matrix::Identity()
	{
		return XMMatrixIdentity();
	}

	Matrix Matrix::Translate(const Vector3& position)
	{
		return Translate(position.x, position.y, position.z);
	}

	Matrix Matrix::Translate(float x, float y, float z)
	{
		return XMMatrixTranslation(x, y, z);
	}

	Matrix Matrix::Scale(float scale)
	{
		return Scale(scale, scale, scale);
	}

	Matrix Matrix::Scale(const Vector3& scale)
	{
		return Scale(scale.x, scale.y, scale.z);
	}

	Matrix Matrix::Scale(float x, float y, float z)
	{
		return XMMatrixScaling(x, y, z);
	}

	Matrix Matrix::RotateX(float angle)
	{
		return XMMatrixRotationX(angle);
	}

	Matrix Matrix::RotateY(float angle)
	{
		return XMMatrixRotationY(angle);
	}

	Matrix Matrix::RotateZ(float angle)
	{
		return XMMatrixRotationZ(angle);
	}

	Matrix Matrix::Rotate(const Vector3& pitchYawRoll)
	{
		return Rotate(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z);
	}

	Matrix Matrix::Rotate(float pitch, float yaw, float roll)
	{
		return XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	}

	Matrix Matrix::Rotate(const Quaternion& q)
	{
		return Identity();
	}

	Matrix Matrix::Transform(
		float scaling,
		const Vector3& rotation,
		const Vector3& translation)
	{
		return Transform(
		{ scaling, scaling, scaling },
			rotation,
			translation);
	}

	Matrix Matrix::Transform(
		const Vector3& scaling,
		const Vector3& rotation,
		const Vector3& translation)
	{

		return XMMatrixAffineTransformation(
			scaling.ToVector(1.0f),
			DirectX::g_XMZero,
			rotation.ToVector(0.0f),
			translation.ToVector(0.0f));
	}

	Matrix Matrix::Transform(
		float scaling,
		const Quaternion& rotation,
		const Vector3& translation)
	{
		return Transform(
		{ scaling, scaling, scaling },
			rotation,
			translation);
	}

	Matrix Matrix::Transform(
		const Vector3& scaling,
		const Quaternion& rotation,
		const Vector3& translation)
	{
		return XMMatrixAffineTransformation(
			scaling.ToVector(1.0f),
			DirectX::g_XMZero,
			rotation.xm,
			translation.ToVector(0.0f));
	}

	Matrix Matrix::Translated(const Vector3& position) const
	{
		return Translated(position.x, position.y, position.z);
	}

	Matrix Matrix::Translated(float x, float y, float z) const
	{
		return *this * Translate(x, y, z);
	}

	Matrix Matrix::Scaled(float scale) const
	{
		return Scaled(scale, scale, scale);
	}

	Matrix Matrix::Scaled(const Vector3& scale) const
	{
		return Scaled(scale.x, scale.y, scale.z);
	}

	Matrix Matrix::Scaled(float x, float y, float z) const
	{
		return *this * Scale(x, y, z);
	}

	Matrix Matrix::RotatedX(float angle) const
	{
		return *this * RotateX(angle);
	}

	Matrix Matrix::RotatedY(float angle) const
	{
		return *this * RotateY(angle);
	}

	Matrix Matrix::RotatedZ(float angle) const
	{
		return *this * RotateZ(angle);
	}

	Matrix Matrix::Rotated(const Vector3& pitchYawRoll) const
	{
		return Rotated(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z);
	}

	Matrix Matrix::Rotated(float pitch, float yaw, float roll) const
	{
		return *this * Rotate(pitch, yaw, roll);
	}

	Matrix Matrix::Rotated(const Quaternion& q) const
	{
		return *this * Rotate(q);
	}

	Matrix Matrix::Transformed(float scaling, const Vector3& rotation, const Vector3& translation) const
	{
		return Transformed({ scaling,scaling ,scaling }, rotation, translation);
	}

	Matrix Matrix::Transformed(const Vector3& scaling, const Vector3& rotation, const Vector3& translation) const
	{
		return *this * Transform(scaling, rotation, translation);
	}

	Matrix Matrix::Transformed(float scaling, const Quaternion& rotation, const Vector3& translation) const
	{
		return Transformed({ scaling,scaling ,scaling }, rotation, translation);
	}

	Matrix Matrix::Transformed(const Vector3& scaling, const Quaternion& rotation, const Vector3& translation) const
	{
		return *this * Transform(scaling, rotation, translation);
	}

	bool Matrix::Decompose(
		Vector3& scale,
		Quaternion& rotation,
		Vector3& translation) const
	{
		XMVECTOR scaleOutput;
		XMVECTOR rotateOutput;
		XMVECTOR translateOutput;
		bool success = XMMatrixDecompose(
			&scaleOutput,
			&rotateOutput,
			&translateOutput,
			*this);

		if (!success)
		{
			return false;
		}

		scale = scaleOutput;
		rotation = rotateOutput;
		translation = translateOutput;

		return true;
	}

	float Matrix::Determinant() const
	{
		auto determinant = XMMatrixDeterminant(*this);
		return
			_11 * determinant.vector4_f32[0] +
			_21 * determinant.vector4_f32[1] +
			_31 * determinant.vector4_f32[2] +
			_41 * determinant.vector4_f32[3];
	}

	Matrix Matrix::Inverse() const
	{
		return XMMatrixInverse(&XMMatrixDeterminant(*this), *this);
	}

	Matrix Matrix::Inverse(float& determinant) const
	{
		determinant = Determinant();
		return Inverse();
	}

	Matrix Matrix::Transposed() const
	{
		return XMMatrixTranspose(*this);
	}

	bool Matrix::IsIdentity() const
	{
		return XMMatrixIsIdentity(*this);
	}

	Matrix operator * (const Matrix& m1, const Matrix& m2)
	{
		Matrix m = m1;
		return m *= m2;
	}

	Matrix& operator *= (Matrix& m1, const Matrix& m2)
	{
		m1 = XMMatrixMultiply(m1, m2);
		return m1;
	}

	Vector3 operator * (const Vector3& v, const Matrix& matrix)
	{
		return XMVector3Transform(v.ToVector(1.0f), matrix);
	}

	Vector3& operator *= (Vector3& v, const Matrix& matrix)
	{
		v = v * matrix;
		return v;
	}
	Vector2 operator * (const Vector2& v, const Matrix& matrix)
	{
		return XMVector2Transform(Vector4(v.x, v.y, 0.0f, 1.0f), matrix);
	}
	Vector2 & operator*=(Vector2& v, const Matrix& matrix)
	{
		v = v * matrix;
		return v;
	}
}

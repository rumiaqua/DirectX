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
		// return Quaternion::ToMatrix(q);
		return Identity();
	}

	Matrix Matrix::Transform(
		const Vector3& scaling,
		const Vector3& rotation,
		const Vector3& translation)
	{

		return XMMatrixAffineTransformation(
			Vector3::ToVector(scaling, 1.0f),
			DirectX::g_XMZero,
			Vector3::ToVector(rotation, 0.0f),
			Vector3::ToVector(translation, 0.0f));
	}

	Matrix Matrix::Transform(
		float scaling,
		const Vector3& rotation,
		const Vector3& translation)
	{
		return Transform(
			Vector3{ scaling, scaling, scaling },
			rotation,
			translation);
	}

	Matrix Matrix::Transform(
		const Vector3& scaling,
		const Quaternion& rotation,
		const Vector3& translation)
	{
		return XMMatrixAffineTransformation(
			Vector3::ToVector(scaling, 1.0f),
			DirectX::g_XMZero,
			rotation.xm,
			Vector3::ToVector(translation, 0.0f));
	}

	Matrix Matrix::Transform(
		float scaling,
		const Quaternion& rotation,
		const Vector3& translation)
	{
		return Transform(
			Vector3 { scaling, scaling, scaling },
			rotation,
			translation);
	}

	bool Matrix::Decompose(
		const Matrix& matrix,
		Vector3& scale,
		Quaternion& rotation,
		Vector3& translation)
	{
		XMVECTOR scaleOutput;
		XMVECTOR rotateOutput;
		XMVECTOR translateOutput;
		bool success = XMMatrixDecompose(
			&scaleOutput,
			&rotateOutput,
			&translateOutput,
			matrix);
		if (!success)
		{
			return false;
		}

		scale = scaleOutput;
		rotation = rotateOutput;
		translation = translateOutput;

		return true;
	}

	float Matrix::Determinant(const Matrix& matrix)
	{
		auto determinant = XMMatrixDeterminant(matrix);
		return
			matrix._11 * determinant.vector4_f32[0] +
			matrix._31 * determinant.vector4_f32[1] +
			matrix._21 * determinant.vector4_f32[2] +
			matrix._41 * determinant.vector4_f32[3];
	}

	Matrix Matrix::Inverse(const Matrix& matrix)
	{
		return XMMatrixInverse(&XMMatrixDeterminant(matrix), matrix);
	}

	Matrix Matrix::Inverse(const Matrix& matrix, float& determinant)
	{
		determinant = Matrix::Determinant(matrix);
		return Inverse(matrix);
	}

	Matrix Matrix::Transpose(const Matrix& matrix)
	{
		return XMMatrixTranspose(matrix);
	}

	bool Matrix::IsIdentity(const Matrix& matrix)
	{
		return XMMatrixIsIdentity(matrix);
	}

	Vector3 operator * (const Vector3& v, const Matrix& matrix)
	{
		return XMVector3Transform(Vector3::ToVector(v, 1.0f), matrix);
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

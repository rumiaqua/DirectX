# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Quaternion;

	class Vector2;

	class Vector3;

	class Matrix : public XMMATRIX
	{
	public:

		/// <summary>デフォルトコンストラクタ</summary>
		Matrix() = default;

		/// <summary>要素を指定</summary>
		Matrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24, 
			float _31, float _32, float _33, float _34, 
			float _41, float _42, float _43, float _44);

		/// <summary>DirectXのベクトルから変換</summary>
		/// <param name="matrix">DirectXの行列</param>
		Matrix(const XMMATRIX& matrix);

		/// <summary>配列に変換</summary>
		/// <returns>配列</returns>
		operator const float* () const;

	public:

		/// <summary>単位行列を返す</summary>
		/// <returns>単位行列</returns>
		static Matrix Identity();

		/// <summary>平行移動行列を返す</summary>
		/// <param name="position">移動量</param>
		/// <returns>平行移動行列</returns>
		static Matrix Translate(const Vector3& position);

		/// <summary>平行移動行列を返す</summary>
		/// <param name="x">x方向の移動量</param>
		/// <param name="y">y方向の移動量</param>
		/// <param name="z">z方向の移動量</param>
		/// <returns>平行移動行列</returns>
		static Matrix Translate(float x, float y, float z);

		/// <summary>拡大縮小行列を返す</summary>
		/// <param name="s">拡大率</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Scale(float scale);

		/// <summary>拡大縮小行列を返す</summary>
		/// <param name="scale">拡大率</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Scale(const Vector3& scale);

		/// <summary>拡大縮小行列を返す</summary>
		/// <param name="x">x方向の拡大率</param>
		/// <param name="y">y方向の拡大率</param>
		/// <param name="z">z方向の拡大率</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Scale(float x, float y, float z);

		/// <summary>回転行列を返す</summary>
		/// <param name="pitch">x軸の回転量</param>
		/// <param name="yaw">y軸の回転量</param>
		/// <param name="roll">z軸の回転量</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Rotate(float pitch, float yaw, float roll);

		/// <summary>回転行列を返す</summary>
		/// <param name="pitchYawRoll">回転量</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Rotate(const Vector3& pitchYawRoll);

		/// <summary>回転行列を返す</summary>
		/// <param name="q">回転量</param>
		/// <returns>拡大縮小行列</returns>
		static Matrix Rotate(const Quaternion& q);

		/// <summary>アフィン変換行列を返す</summary>
		/// <param name="scaling">拡大率</param>
		/// <param name="rotation">回転量</param>
		/// <param name="translation">移動量</param>
		/// <returns>アフィン変換行列</returns>
		static Matrix Transform(
			const Vector3& scaling,
			const Vector3& rotation,
			const Vector3& translation);

		/// <summary>アフィン変換行列を返す</summary>
		/// <param name="scaling">拡大率</param>
		/// <param name="rotation">回転量</param>
		/// <param name="translation">移動量</param>
		/// <returns>アフィン変換行列</returns>
		static Matrix Transform(
			float scaling,
			const Vector3& rotation,
			const Vector3& translation);

		/// <summary>アフィン変換行列を返す</summary>
		/// <param name="scaling">拡大率</param>
		/// <param name="rotation">回転量</param>
		/// <param name="translation">移動量</param>
		/// <returns>アフィン変換行列</returns>
		static Matrix Transform(
			const Vector3& scaling,
			const Quaternion& rotation,
			const Vector3& translation);

		/// <summary>アフィン変換行列を返す</summary>
		/// <param name="scaling">拡大率</param>
		/// <param name="rotation">回転量</param>
		/// <param name="translation">移動量</param>
		/// <returns>アフィン変換行列</returns>
		static Matrix Transform(
			float scaling,
			const Quaternion& rotation,
			const Vector3& translation);

		/// <summary>分解して引数に収納する</summary>
		/// <param name="scaling">拡大率</param>
		/// <param name="rotation">回転量</param>
		/// <param name="translation">移動量</param>
		/// <returns>成功すればtrue そうでなければfalse</returns>
		static bool Decompose(
			const Matrix& matrix,
			Vector3& scale,
			Quaternion& rotation,
			Vector3& translation);

		/// <summary>行列式を返す</summary>
		/// <param name="matrix">行列</param>
		/// <returns>行列式</returns>
		static float Determinant(const Matrix& matrix);

		/// <summary>逆行列を返す</summary>
		/// <param name="matrix">行列</param>
		/// <returns>逆行列</returns>
		static Matrix Inverse(const Matrix& matrix);

		/// <summary>行列式を収納して逆行列を返す</summary>
		/// <param name="matrix">行列</param>
		/// <param name="determinant">行列式</param>
		/// <returns>逆行列</returns>
		static Matrix Inverse(const Matrix& matrix, float& determinant);

		/// <summary>転置行列を返す</summary>
		/// <param name="matrix">行列</param>
		/// <returns>転置行列</returns>
		static Matrix Transpose(const Matrix& matrix);

		/// <summary>単位行列かどうかを返す</summary>
		/// <param name="matrix">行列</param>
		/// <returns>単位行列であればtrue そうでなければfalse</returns>
		static bool IsIdentity(const Matrix& matrix);

	};

	Vector3 operator * (const Vector3& v, const Matrix& matrix);

	Vector3& operator *= (Vector3& v, const Matrix& matrix);

	Vector2 operator * (const Vector2& v, const Matrix& matrix);

	Vector2& operator *= (Vector2& v, const Matrix& matrix);
}

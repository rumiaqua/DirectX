# pragma once

namespace aqua
{
	class Matrix;

	class Vector2;

	class Vector3;

	class Quaternion
	{
	public:

		/// <summary>デフォルトコンストラクタ</summary>
		Quaternion() = default;

		/// <summary>要素を指定する</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		/// <param name="w">w</param>
		Quaternion(float x, float y, float z, float w);

		/// <summary>回転軸を回転量を指定する</summary>
		/// <param name="axis">回転軸</param>
		/// <param name="angle">回転量</param>
		Quaternion(const Vector3& axis, float angle);

		/// <summary>DirectXのベクトルから変換する</summary>
		/// <param name="v">DirectXのベクトル</param>
		Quaternion(const DirectX::XMVECTOR& v);

	public:

		/// <summary>単位クォータニオンを返す</summary>
		/// <returns>単位クォータニオン</returns>
		static Quaternion Identity();

		/// <summary>z軸回転したクォータニオンを返す</summary>
		/// <param name="angle">回転量</param>
		/// <returns>クォータニオン</returns>
		static Quaternion Roll(float angle);

		/// <summary>x軸回転したクォータニオンを返す</summary>
		/// <param name="angle">回転量</param>
		/// <returns>クォータニオン</returns>
		static Quaternion Pitch(float angle);

		/// <summary>y軸回転したクォータニオンを返す</summary>
		/// <param name="angle">回転量</param>
		/// <returns>クォータニオン</returns>
		static Quaternion Yaw(float angle);

		/// <summary>3軸回転したクォータニオンを返す</summary>
		/// <param name="roll">z軸回転料</param>
		/// <param name="pitch">x軸回転量</param>
		/// <param name="yaw">y軸回転量</param>
		/// <returns>クォータニオン</returns>
		static Quaternion RollPitchYaw(float roll, float pitch, float yaw);

		/// <summary>正規化されたクォータニオンを返す</summary>
		/// <param name="q">クォータニオン</param>
		/// <returns>正規化されたクォータニオン</returns>
		static Quaternion Normalize(const Quaternion& q);

		/// <summary>行列に変換する</summary>
		/// <param name="q">クォータニオン</param>
		/// <returns>行列</returns>
		static Matrix ToMatrix(const Quaternion& q);

		/// <summary>単位クォータニオンかどうか返す</summary>
		/// <param name="q">クォータニオン</param>
		/// <returns>単位クォータニオンであればtrue そうでなければfalse</returns>
		static bool IsIdentity(const Quaternion& q);

	public:

		union
		{
			/// <summary>DirectXベクトル</summary>
			DirectX::XMVECTOR xm;

			/// <summary>配列</summary>
			float elm[4];

			/// <summary>要素</summary>
			struct
			{
				float x, y, z, w;
			};
		};
	};

	Quaternion operator * (const Quaternion& q, const Quaternion& p);

	Quaternion& operator *= (Quaternion& q, const Quaternion& p);

	Vector2 operator * (const Vector2& v, const Quaternion& q);

	Vector2 operator *= (Vector2& v, const Quaternion& q);

	Vector3 operator * (const Vector3& v, const Quaternion& q);

	Vector3 operator *= (Vector3& v, const Quaternion& q);
}

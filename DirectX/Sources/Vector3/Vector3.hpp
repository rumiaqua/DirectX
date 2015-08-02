# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector2;

	class Vector4;

	class Vector3
	{
	public:

		/// <summary>零ベクトル</summary>
		static const Vector3 Zero;

		/// <summary>(1, 1, 1)のベクトル</summary>
		static const Vector3 One;

		/// <summary>(-1, 0, 0)のベクトル</summary>
		static const Vector3 Left;

		/// <summary>(1, 0, 0)のベクトル</summary>
		static const Vector3 Right;

		/// <summary>(0, 1, 0)のベクトル</summary>
		static const Vector3 Up;

		/// <summary>(0, -1, 0)のベクトル</summary>
		static const Vector3 Down;

		/// <summary>(0, 0, 1)のベクトル</summary>
		static const Vector3 Forward;

		/// <summary>(0, 0, -1)のベクトル</summary>
		static const Vector3 Backward;

	public:

		/// <summary>デフォルトコンストラクタ</summary>
		Vector3();

		/// <summary>コピーコンストラクタ</summary>
		/// <param name="v">ベクトル</param>
		Vector3(const Vector3& other);

		/// <summary>DirectXベクトルから変換</summary>
		/// <param name="v">DirectXベクトル</param>
		Vector3(const XMVECTOR& xm);

		/// <summary>二次元ベクトルから変換</summary>
		/// <param name="v">二次元ベクトル</param>
		/// <param name="z">z要素</param>
		Vector3(const Vector2& v, float z = -1.0f);

		/// <summary>四次元ベクトルから変換</summary>
		/// <param name="v">四次元ベクトル</param>
		Vector3(const Vector4& v);

		/// <summary>要素を指定する</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		Vector3(float x, float y, float z);

	public:

		/// <summary>コピー演算子</summary>
		/// <param name="other">ベクトル</param>
		/// <returns>自身</returns>
		Vector3& operator = (const Vector3& other);

	public:

		/// <summary>長さの二乗を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さの二乗</returns>
		static float LengthSquared(const Vector3& v);

		/// <summary>長さを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さ</returns>
		static float Length(const Vector3& v);

		/// <summary>正規化されたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>正規化されたベクトル</returns>
		static Vector3 Normalize(const Vector3& v);

		/// <summary>0から1の間にクランプされたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>0から1の間にクランプされたベクトル</returns>
		static Vector3 Saturate(const Vector3& v);

		/// <summary>指定桁数でならしたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>ならしたベクトル</returns>
		static Vector3 Smooth(const Vector3& v, int f = -4);

		/// <summary>内積を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>内積</returns>
		static float Dot(const Vector3& v1, const Vector3& v2);

		/// <summary>外積を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>外積</returns>
		static Vector3 Cross(const Vector3& v1, const Vector3& v2);

		/// <summary>DirectXのベクトルに変換する</summary>
		/// <param name="v">ベクトル</param>
		/// <param name="w">w要素の値</param>
		/// <returns>DirectXのベクトル</returns>
		static XMVECTOR ToVector(const Vector3& v, float w = 1.0f);

		/// <summary>距離を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>距離</returns>
		static float Distance(const Vector3& v1, const Vector3& v2);

		/// <summary>壁ずりベクトルを返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">法線ベクトル</param>
		/// <returns>壁ずりベクトル</returns>
		static Vector3 Scratch(const Vector3& v, const Vector3& normal);

		/// <summary>反射ベクトルを返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">法線ベクトル</param>
		/// <returns>反射ベクトル</returns>
		static Vector3 Reflect(const Vector3& v, const Vector3& normal);

		/// <summary>射影ベクトルを返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">対象のベクトル</param>
		/// <returns>射影ベクトル</returns>
		static Vector3 Projection(const Vector3& v, const Vector3& target);

		/// <summary>線形補間したベクトルを返す</summary>
		/// <param name="v1">始点</param>
		/// <param name="v2">終点</param>
		/// <param name="t">比率</param>
		/// <returns>補間ベクトル</returns>
		static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	public:

		union
		{
			/// <summary>色</summary>
			struct
			{
				float r;

				float g;

				float b;
			};

			/// <summary>座標</summary>
			struct
			{
				float x;

				float y;

				float z;
			};

			/// <summary>配列</summary>
			float elm[3];
		};
	};

	bool operator == (const Vector3& v1, const Vector3& v2);

	bool operator != (const Vector3& v1, const Vector3& v2);

	Vector3 operator + (const Vector3& v);

	Vector3 operator - (const Vector3& v);

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
}

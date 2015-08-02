# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector3;

	class Vector2
	{
	public:

		/// <summary>零ベクトル</summary>
		static const Vector2 Zero;

		/// <summary>(1, 1)のベクトル</summary>
		static const Vector2 One;

		/// <summary>(-1, 0)のベクトル</summary>
		static const Vector2 Left;

		/// <summary>(1, 0)のベクトル</summary>
		static const Vector2 Right;

		/// <summary>(0, -1)のベクトル</summary>
		static const Vector2 Up;

		/// <summary>(0, 1)のベクトル</summary>
		static const Vector2 Down;

		// constructor
	public:

		/// <summary>デフォルトコンストラクタ</summary>
		Vector2();

		/// <summary>コピーコンストラクタ</summary>
		/// <param name="v">ベクトル</param>
		Vector2(const Vector2& other);

		/// <summary>DirectXベクトルから変換</summary>
		/// <param name="v">DirectXベクトル</param>
		Vector2(const XMVECTOR& xm);

		/// <summary>要素を指定する</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		Vector2(float x, float y);

		/// <summary>コピー演算子</summary>
		/// <param name="other">ベクトル</param>
		/// <returns>自身</returns>
		Vector2& operator = (const Vector2& other);

	public:

		/// <summary>長さの二乗を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さの二乗</returns>
		static float LengthSquared(const Vector2& v);

		/// <summary>長さを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さ</returns>
		static float Length(const Vector2& v);

		/// <summary>正規化されたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>正規化されたベクトル</returns>
		static Vector2 Normalize(const Vector2& v);

		/// <summary>0から1の間にクランプされたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>0から1の間にクランプされたベクトル</returns>
		static Vector2 Saturate(const Vector2& v);

		/// <summary>指定桁数でならしたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>ならしたベクトル</returns>
		static Vector2 Smooth(const Vector2& v, int f = -4);

		// binary math method

		/// <summary>内積を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>内積</returns>
		static float Dot(const Vector2& v1, const Vector2& v2);

		/// <summary>外積を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>外積</returns>
		static float Cross(const Vector2& v1, const Vector2& v2);

		/// <summary>距離を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>距離</returns>
		static float Distance(const Vector2& v1, const Vector2& v2);

		/// <summary>線形補間したベクトルを返す</summary>
		/// <param name="v1">始点</param>
		/// <param name="v2">終点</param>
		/// <param name="t">比率</param>
		/// <returns>補間ベクトル</returns>
		static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t);

	public:

		union
		{
			/// <summary>UV</summary>
			struct
			{
				float u;

				float v;
			};

			/// <summary>座標</summary>
			struct
			{
				float x;

				float y;
			};

			/// <summary>配列</summary>
			float elm[2];
		};
	};

	bool operator == (const Vector2& v1, const Vector2& v2);

	bool operator != (const Vector2& v1, const Vector2& v2);

	Vector2 operator + (const Vector2& v);

	Vector2 operator - (const Vector2& v);

	Vector2& operator += (Vector2& v1, const Vector2& v2);

	Vector2& operator -= (Vector2& v1, const Vector2& v2);

	Vector2& operator *= (Vector2& v, float s);

	Vector2& operator *= (float s, Vector2& v);

	Vector2& operator /= (Vector2& v, float s);

	Vector2 operator + (const Vector2& v1, const Vector2& v2);

	Vector2 operator - (const Vector2& v1, const Vector2& v2);

	Vector2 operator * (const Vector2& v, float s);

	Vector2 operator * (float s, const Vector2& v);

	Vector2 operator / (const Vector2& v, float s);
}

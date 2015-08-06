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

		Vector3& operator = (const Vector3& other);

	public:

		/// <summary>長さの二乗を返す</summary>
		/// <returns>長さの二乗</returns>
		float LengthSquared() const;

		/// <summary>長さを返す</summary>
		/// <returns>長さ</returns>
		float Length() const;

		/// <summary>正規化されたベクトルを返す</summary>
		/// <returns>正規化されたベクトル</returns>
		Vector3 Normalized() const;

		/// <summary>0から1の間にクランプされたベクトルを返す</summary>
		/// <returns>0から1の間にクランプされたベクトル</returns>
		Vector3 Saturated() const;

		/// <summary>指定桁数でならしたベクトルを返す</summary>
		/// <returns>ならしたベクトル</returns>
		Vector3 Smoothed(int f = -4) const;

		/// <summary>内積を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>内積</returns>
		float Dot(const Vector3& v) const;

		/// <summary>外積を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>外積</returns>
		Vector3 Cross(const Vector3& v) const;

		/// <summary>DirectXのベクトルに変換する</summary>
		/// <param name="w">w要素の値</param>
		/// <returns>DirectXのベクトル</returns>
		XMVECTOR ToVector(float w = 1.0f) const;

		/// <summary>距離を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>距離</returns>
		float Distance(const Vector3& v) const;

		/// <summary>壁ずりベクトルを返す</summary>
		/// <param name="normal">法線ベクトル</param>
		/// <returns>壁ずりベクトル</returns>
		Vector3 Scratched(const Vector3& normal) const;

		/// <summary>反射ベクトルを返す</summary>
		/// <param name="normal">法線ベクトル</param>
		/// <returns>反射ベクトル</returns>
		Vector3 Reflected(const Vector3& normal) const;

		/// <summary>射影ベクトルを返す</summary>
		/// <param name="target">対象のベクトル</param>
		/// <returns>射影ベクトル</returns>
		Vector3 Projected(const Vector3& target) const;

	public:

		/// <summary>正規化する</summary>
		/// <returns>ベクトル</returns>
		Vector3& Normalize();

		/// <summary>0から1の間にクランプする</summary>
		/// <returns>ベクトル</returns>
		Vector3& Saturate();

		/// <summary>指定桁数でならす</summary>
		/// <returns>ベクトル</returns>
		Vector3& Smooth(int f = -4);

		/// <summary>壁ずりベクトルを計算する</summary>
		/// <param name="normal">法線ベクトル</param>
		/// <returns>ベクトル</returns>
		Vector3& Scratch(const Vector3& normal);

		/// <summary>反射ベクトルを計算する</summary>
		/// <param name="normal">法線ベクトル</param>
		/// <returns>ベクトル</returns>
		Vector3& Reflect(const Vector3& normal);

		/// <summary>射影ベクトルを計算する</summary>
		/// <param name="target">対象のベクトル</param>
		/// <returns>ベクトル</returns>
		Vector3& Project(const Vector3& target);

	public:

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

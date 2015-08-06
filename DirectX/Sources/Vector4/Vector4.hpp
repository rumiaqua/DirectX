# pragma once

# include <DirectXPackedVector.h>

namespace aqua
{
	using namespace DirectX;

	class Vector2;

	class Vector3;

	class Vector4
	{
	public:

		/// <summary>零ベクトル</summary>
		static const Vector4 Zero;

		/// <summary>(1, 1, 1, 1)のベクトル</summary>
		static const Vector4 One;

	public:

		/// <summary>デフォルトコンストラクタ</summary>
		Vector4();

		/// <summary>コピーコンストラクタ</summary>
		/// <param name="v">ベクトル</param>
		Vector4(const Vector4& other);

		/// <summary>DirectXベクトルから変換</summary>
		/// <param name="v">DirectXベクトル</param>
		Vector4(const XMVECTOR& xm);

		/// <summary>二次元ベクトル２つから変換</summary>
		/// <param name="v1">xy二次元ベクトル</param>
		/// <param name="v2">zw二次元ベクトル</param>
		Vector4(const Vector2& v1, const Vector2& v2);

		/// <summary>三次元ベクトルから変換</summary>
		/// <param name="v">三次元ベクトル</param>
		/// <param name="w">w要素</param>
		Vector4(const Vector3& v, float w);

		/// <summary>要素を指定する</summary>
		/// <param name="x">x要素</param>
		/// <param name="y">y要素</param>
		/// <param name="z">z要素</param>
		/// <param name="w">w要素</param>
		Vector4(float x, float y, float z, float w);

	public:

		Vector4& operator = (const Vector4& other);

	public:

		operator XMVECTOR();

		operator const XMVECTOR() const;

		operator float* ();

		operator const float* () const;

		XMVECTOR* operator & ();

		const XMVECTOR* operator & () const;

	public:

		/// <summary>長さの二乗を返す</summary>
		/// <returns>長さの二乗</returns>
		float LengthSquared() const;

		/// <summary>長さを返す</summary>
		/// <returns>長さ</returns>
		float Length() const;

		/// <summary>正規化されたベクトルを返す</summary>
		/// <returns>正規化されたベクトル</returns>
		Vector4 Normalized() const;

		/// <summary>0から1の間にクランプされたベクトルを返す</summary>
		/// <returns>0から1の間にクランプされたベクトル</returns>
		Vector4 Saturated() const;

		/// <summary>指定桁数でならしたベクトルを返す</summary>
		/// <returns>ならしたベクトル</returns>
		Vector4 Smoothed(int f = -4) const;

		/// <summary>内積を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>内積</returns>
		float Dot(const Vector4& v) const;

		/// <summary>距離を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>距離</returns>
		float Distance(const Vector4& v) const;

	public:

		/// <summary>正規化する</summary>
		/// <returns>ベクトル</returns>
		Vector4& Normalize();

		/// <summary>0から1の間にクランプする</summary>
		/// <returns>ベクトル</returns>
		Vector4& Saturate();

		/// <summary>指定桁数でならす</summary>
		/// <returns>ベクトル</returns>
		Vector4& Smooth(int f = -4);

	public:

		/// <summary>線形補間したベクトルを返す</summary>
		/// <param name="v1">始点</param>
		/// <param name="v2">終点</param>
		/// <param name="t">比率</param>
		/// <returns>補間ベクトル</returns>
		static Vector4 Lerp(const Vector4& v1, const Vector4& v2, float t);

	public:

		union
		{
			/// <summary>色</summary>
			struct
			{
				float r;

				float g;

				float b;

				float a;
			};

			/// <summary>座標</summary>
			struct
			{
				float x;

				float y;

				float z;
				
				float w;
			};

			/// <summary>配列</summary>
			float elm[4];

			XMVECTOR xm;
		};
	};

	bool operator == (const Vector4& v1, const Vector4& v2);

	bool operator != (const Vector4& v1, const Vector4& v2);

	Vector4 operator + (const Vector4& v);

	Vector4 operator - (const Vector4& v);

	Vector4& operator += (Vector4& v1, const Vector4& v2);

	Vector4& operator -= (Vector4& v1, const Vector4& v2);

	Vector4& operator *= (Vector4& v, float s);

	Vector4& operator *= (float s, Vector4& v);

	Vector4& operator /= (Vector4& v, float s);

	Vector4 operator + (const Vector4& v1, const Vector4& v2);

	Vector4 operator - (const Vector4& v1, const Vector4& v2);

	Vector4 operator * (const Vector4& v, float s);

	Vector4 operator * (float s, const Vector4& v);

	Vector4 operator / (const Vector4& v, float s);
}

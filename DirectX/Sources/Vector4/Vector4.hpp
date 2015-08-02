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

		/// <summmary>(1, 1, 1)のベクトル</summary>
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
		/// <param name="w">w要素の値</param>
		Vector4(const Vector3& v, float w);

		/// <summary>要素を指定する</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		Vector4(float x, float y, float z, float w);

	public:

		/// <summary>コピー演算子</summary>
		/// <param name="other">ベクトル</param>
		/// <returns>自身</returns>
		Vector4& operator = (const Vector4& other);

		/// <summary>DirectXベクトルに変換</summary>
		/// <param>DirectXベクトル</param>
		operator XMVECTOR();

		/// <summary>DirectXベクトルに変換</summary>
		/// <returns>DirectXベクトル</returns>
		operator const XMVECTOR() const;

		/// <summary>配列に変換</summary>
		/// <returns>配列</returns>
		operator float* ();

		/// <summary>配列に変換</summary>
		/// <returns>配列</returns>
		operator const float* () const;

		/// <summary>DirectXベクトルのポインタに変換</summary>
		/// <returns>DirectXベクトルのポインタ</returns>
		XMVECTOR* operator & ();

		/// <summary>DirectXベクトルのconstポインタに変換</summary>
		/// <returns>DirectXベクトルのconstポインタ</returns>
		const XMVECTOR* operator & () const;

	public:

		/// <summary>長さの二乗を返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さの二乗</returns>
		static float LengthSquared(const Vector4& v);

		/// <summary>長さを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>長さ</returns>
		static float Length(const Vector4& v);

		/// <summary>正規化されたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>正規化されたベクトル</returns>
		static Vector4 Normalize(const Vector4& v);

		/// <summary>0から1の間にクランプされたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>0から1の間にクランプされたベクトル</returns>
		static Vector4 Saturate(const Vector4& v);

		/// <summary>指定桁数でならしたベクトルを返す</summary>
		/// <param name="v">ベクトル</param>
		/// <returns>ならしたベクトル</returns>
		static Vector4 Smooth(const Vector4& v, int f = -4);

		/// <summary>内積を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>内積</returns>
		static float Dot(const Vector4& v1, const Vector4& v2);

		/// <summary>距離を返す</summary>
		/// <param name="v1">ベクトル</param>
		/// <param name="v2">ベクトル</param>
		/// <returns>距離</returns>
		static float Distance(const Vector4& v1, const Vector4& v2);

		/// <summary>線形補間したベクトルを返す</summary>
		/// <param name="v1">始点</param>
		/// <param name="v2">終点</param>
		/// <param name="t">比率</param>
		/// <returns>補間ベクトル</returns>
		static Vector4 Lerp(const Vector4& v1, const Vector4& v2, float t);

	public:

		union
		{
			/// <summary>DirectX</summary>
			XMVECTOR xm;

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

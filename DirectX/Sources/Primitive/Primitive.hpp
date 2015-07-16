# pragma once

# include <DirectXPackedVector.h>

// 二次元ベクトル
struct Float2
{
	Float2()
		: Float2(0.0f, 0.0f)
	{

	}

	Float2(const float* element)
		: Float2(element[0], element[1])
	{

	}

	Float2(const DirectX::XMFLOAT2& f)
		: Float2(f.x, f.y)
	{

	}

	Float2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	operator float*()
	{
		return elm;
	}

	operator const float*() const
	{
		return elm;
	}

	operator DirectX::XMFLOAT2()
	{
		return DirectX::XMFLOAT2(elm);
	}

	union
	{
		// 座標
		struct
		{
			float x, y;
		};

		// 要素配列
		float elm[2];

		// テクスチャ座標
		struct
		{
			float u, v;
		};
	};
};

// 三次元ベクトル
struct Float3
{
	Float3()
		: Float3(0.0f, 0.0f, 0.0f)
	{

	}

	Float3(const float* element)
		: Float3(element[0], element[1], element[2])
	{

	}

	Float3(const DirectX::XMFLOAT3& f)
		: Float3(f.x, f.y, f.z)
	{

	}

	Float3(const DirectX::XMVECTOR& v)
		: Float3(v.vector4_f32[0], v.vector4_f32[1], v.vector4_f32[2])
	{

	}

	Float3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{

	}

	operator float*()
	{
		return elm;
	}

	operator const float*() const
	{
		return elm;
	}

	operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(elm);
	}

	DirectX::XMVECTOR ToVector(float w = 1.0f) const
	{
		return DirectX::XMVectorSet(x, y, z, w);
	}

	union
	{
		// 座標
		struct
		{
			float x, y, z;
		};

		// 要素配列
		float elm[3];

		// 色
		struct
		{
			float r, g, b;
		};
	};
};

// 四次元ベクトル
struct Float4
{
	Float4()
		: Float4(0.0f, 0.0f, 0.0f, 0.0f)
	{

	}

	Float4(const float* element)
		: Float4(element[0], element[1], element[2], element[3])
	{

	}

	Float4(const DirectX::XMFLOAT4& f)
		: Float4(f.x, f.y, f.z, f.w)
	{

	}

	Float4(const DirectX::XMVECTOR& v)
		: Float4(v.vector4_f32[0], v.vector4_f32[1], v.vector4_f32[2], v.vector4_f32[3])
	{

	}

	Float4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{

	}

	operator float*()
	{
		return elm;
	}

	operator const float*() const
	{
		return elm;
	}

	operator DirectX::XMFLOAT4()
	{
		return DirectX::XMFLOAT4(elm);
	}

	DirectX::XMVECTOR ToVector() const
	{
		return DirectX::XMVectorSet(x, y, z, w);
	}

	union
	{
		// 座標
		struct
		{
			float x, y, z, w;
		};

		// 要素配列
		float elm[4];

		// 色
		struct
		{
			float r, g, b, a;
		};
	};
};

// 行列
struct Matrix
{
	Matrix()
		: Matrix(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f)
	{

	}

	Matrix(const float* m)
		: Matrix(
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15])
	{

	}

	Matrix(const DirectX::XMMATRIX& matrix)
		: Matrix(
		/*matrix.r[0].m128_f32[0], matrix.r[0].m128_f32[1], matrix.r[0].m128_f32[2], matrix.r[0].m128_f32[3],
		matrix.r[1].m128_f32[0], matrix.r[1].m128_f32[1], matrix.r[1].m128_f32[2], matrix.r[1].m128_f32[3],
		matrix.r[2].m128_f32[0], matrix.r[2].m128_f32[1], matrix.r[2].m128_f32[2], matrix.r[2].m128_f32[3],
		matrix.r[3].m128_f32[0], matrix.r[3].m128_f32[1], matrix.r[3].m128_f32[2], matrix.r[3].m128_f32[3])*/
		matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], matrix.m[0][3],
		matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], matrix.m[1][3],
		matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], matrix.m[2][3],
		matrix.m[3][0], matrix.m[3][1], matrix.m[3][2], matrix.m[3][3])
	{
		
	}

	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
		: m11(m11)
		, m12(m12)
		, m13(m13)
		, m14(m14)
		, m21(m21)
		, m22(m22)
		, m23(m23)
		, m24(m24)
		, m31(m31)
		, m32(m32)
		, m33(m33)
		, m34(m34)
		, m41(m41)
		, m42(m42)
		, m43(m43)
		, m44(m44)
	{

	}

	operator float*()
	{
		return m;
	}

	operator const float*() const
	{
		return m;
	}

	operator DirectX::XMMATRIX() const
	{
		return DirectX::XMMATRIX(m);
	}

	Matrix operator * (const Matrix& other)
	{
		return DirectX::XMMatrixMultiply(*this, other);
	}

	union
	{
		// 要素
		struct
		{
			float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
		};

		// 要素配列
		float m[16];
	};
};

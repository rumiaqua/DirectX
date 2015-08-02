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

		/// <summary>��x�N�g��</summary>
		static const Vector4 Zero;

		/// <summmary>(1, 1, 1)�̃x�N�g��</summary>
		static const Vector4 One;

	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		Vector4();

		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name="v">�x�N�g��</param>
		Vector4(const Vector4& other);

		/// <summary>DirectX�x�N�g������ϊ�</summary>
		/// <param name="v">DirectX�x�N�g��</param>
		Vector4(const XMVECTOR& xm);

		/// <summary>�񎟌��x�N�g���Q����ϊ�</summary>
		/// <param name="v1">xy�񎟌��x�N�g��</param>
		/// <param name="v2">zw�񎟌��x�N�g��</param>
		Vector4(const Vector2& v1, const Vector2& v2);

		/// <summary>�O�����x�N�g������ϊ�</summary>
		/// <param name="v">�O�����x�N�g��</param>
		/// <param name="w">w�v�f�̒l</param>
		Vector4(const Vector3& v, float w);

		/// <summary>�v�f���w�肷��</summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="z">z</param>
		Vector4(float x, float y, float z, float w);

	public:

		/// <summary>�R�s�[���Z�q</summary>
		/// <param name="other">�x�N�g��</param>
		/// <returns>���g</returns>
		Vector4& operator = (const Vector4& other);

		/// <summary>DirectX�x�N�g���ɕϊ�</summary>
		/// <param>DirectX�x�N�g��</param>
		operator XMVECTOR();

		/// <summary>DirectX�x�N�g���ɕϊ�</summary>
		/// <returns>DirectX�x�N�g��</returns>
		operator const XMVECTOR() const;

		/// <summary>�z��ɕϊ�</summary>
		/// <returns>�z��</returns>
		operator float* ();

		/// <summary>�z��ɕϊ�</summary>
		/// <returns>�z��</returns>
		operator const float* () const;

		/// <summary>DirectX�x�N�g���̃|�C���^�ɕϊ�</summary>
		/// <returns>DirectX�x�N�g���̃|�C���^</returns>
		XMVECTOR* operator & ();

		/// <summary>DirectX�x�N�g����const�|�C���^�ɕϊ�</summary>
		/// <returns>DirectX�x�N�g����const�|�C���^</returns>
		const XMVECTOR* operator & () const;

	public:

		/// <summary>�����̓���Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>�����̓��</returns>
		static float LengthSquared(const Vector4& v);

		/// <summary>������Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>����</returns>
		static float Length(const Vector4& v);

		/// <summary>���K�����ꂽ�x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>���K�����ꂽ�x�N�g��</returns>
		static Vector4 Normalize(const Vector4& v);

		/// <summary>0����1�̊ԂɃN�����v���ꂽ�x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>0����1�̊ԂɃN�����v���ꂽ�x�N�g��</returns>
		static Vector4 Saturate(const Vector4& v);

		/// <summary>�w�茅���łȂ炵���x�N�g����Ԃ�</summary>
		/// <param name="v">�x�N�g��</param>
		/// <returns>�Ȃ炵���x�N�g��</returns>
		static Vector4 Smooth(const Vector4& v, int f = -4);

		/// <summary>���ς�Ԃ�</summary>
		/// <param name="v1">�x�N�g��</param>
		/// <param name="v2">�x�N�g��</param>
		/// <returns>����</returns>
		static float Dot(const Vector4& v1, const Vector4& v2);

		/// <summary>������Ԃ�</summary>
		/// <param name="v1">�x�N�g��</param>
		/// <param name="v2">�x�N�g��</param>
		/// <returns>����</returns>
		static float Distance(const Vector4& v1, const Vector4& v2);

		/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
		/// <param name="v1">�n�_</param>
		/// <param name="v2">�I�_</param>
		/// <param name="t">�䗦</param>
		/// <returns>��ԃx�N�g��</returns>
		static Vector4 Lerp(const Vector4& v1, const Vector4& v2, float t);

	public:

		union
		{
			/// <summary>DirectX</summary>
			XMVECTOR xm;

			/// <summary>�F</summary>
			struct
			{
				float r;

				float g;

				float b;

				float a;
			};

			/// <summary>���W</summary>
			struct
			{
				float x;

				float y;

				float z;

				float w;
			};

			/// <summary>�z��</summary>
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

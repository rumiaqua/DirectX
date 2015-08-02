# pragma once

# include <string>

# include <vector>

namespace aqua
{
	class String
	{
	public:

		/// <summary>�f�t�H���g�R���X�g���N�^</summary>
		String();

		/// <summary>�}���`�o�C�g������ŏ�����</summary>
		/// <param name="str">�}���`�o�C�g������</param>
		String(const char* str);

		/// <summary>���C�h������ŏ�����</summary>
		/// <param name="str">���C�h������</param>
		String(const wchar_t* str);

		/// <summary>string�N���X�ŏ�����</summary>
		/// <param name="str">string�N���X</param>
		String(const std::string& str);

		/// <summary>wstring�N���X�ŏ�����</summary>
		/// <param name="str">wstring�N���X</param>
		String(const std::wstring& str);

		struct Hash
		{

		};

	public:

		/// <summary>�}���`�o�C�g������ɕϊ�</summary>
		/// <returns>�}���`�o�C�g������</summary>
		operator const char* () const;

		/// <summary>���C�h������ɕϊ�</summary>
		/// <returns>���C�h������</summary>
		operator const wchar_t* () const;

		/// <summary>������Z�q</summary>
		/// <param name="str">������</param>
		String& operator = (const String& str);

		/// <summary>�w�肵���C���f�b�N�X�̕�����Ԃ�</summary>
		/// <param name="index">�C���f�b�N�X</param>
		wchar_t operator [] (unsigned int index) const;

	public:

		/// <summary>������̒�����Ԃ�</summary>
		/// <param name="str">������</param>
		static unsigned int Length(const String& str);

		/// <summary>string�N���X�ɕϊ�</summary>
		/// <param name="str">������</param>
		static std::string ToNarrow(const String& str);

		/// <summary>wstring�N���X�ɕϊ�</summary>
		/// <param name="str">������</param>
		static std::wstring ToWide(const String& str);

		/// <summary>�������ĕԂ�</summary>
		/// <param name="str">������</param>
		/// <param name="delim">��������</param>
		/// <returns>�������Ď��[�������X�g</returns>
		static std::vector<String> Split(const String& str, wchar_t delim);

	private:

		/// <summary>wstring�N���X</summary>
		std::wstring m_str;
	};
}

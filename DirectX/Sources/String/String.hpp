# pragma once

# include <string>

# include <vector>

# include <hash_map>

namespace aqua
{
	class String
	{
	public:

		/// <summary>デフォルトコンストラクタ</summary>
		String();

		/// <summary>マルチバイト文字列で初期化</summary>
		/// <param name="str">マルチバイト文字列</param>
		String(const char* str);

		/// <summary>ワイド文字列で初期化</summary>
		/// <param name="str">ワイド文字列</param>
		String(const wchar_t* str);

		/// <summary>stringクラスで初期化</summary>
		/// <param name="str">stringクラス</param>
		String(const std::string& str);

		/// <summary>wstringクラスで初期化</summary>
		/// <param name="str">wstringクラス</param>
		String(const std::wstring& str);

	public:

		operator const wchar_t* () const;

	public:

		String& operator = (const String& str);

		bool operator == (const wchar_t* str) const;

		bool operator == (const String& str) const;

		wchar_t operator [] (unsigned int index) const;

	public:

		/// <summary>文字列の長さを返す</summary>
		/// <param name="str">文字列</param>
		unsigned int Length() const;

		/// <summary>stringクラスに変換</summary>
		/// <param name="str">文字列</param>
		std::string ToNarrow() const;

		/// <summary>wstringクラスに変換</summary>
		/// <param name="str">文字列</param>
		std::wstring ToWide() const;

		/// <summary>分割して返す</summary>
		/// <param name="str">文字列</param>
		/// <param name="delim">分割文字</param>
		/// <returns>分割して収納したリスト</returns>
		std::vector<String> Split(wchar_t delim) const;

	private:

		std::wstring m_str;
	};
}

namespace std
{
	template <>
	class hash<String>
	{
	public:
		size_t operator()(const String& str) const
		{
			return hash<std::wstring>()(str.ToWide());
		}
	};
}

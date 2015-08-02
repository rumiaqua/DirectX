# pragma once

# include <string>

# include <vector>

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

		struct Hash
		{

		};

	public:

		/// <summary>マルチバイト文字列に変換</summary>
		/// <returns>マルチバイト文字列</summary>
		operator const char* () const;

		/// <summary>ワイド文字列に変換</summary>
		/// <returns>ワイド文字列</summary>
		operator const wchar_t* () const;

		/// <summary>代入演算子</summary>
		/// <param name="str">文字列</param>
		String& operator = (const String& str);

		/// <summary>指定したインデックスの文字を返す</summary>
		/// <param name="index">インデックス</param>
		wchar_t operator [] (unsigned int index) const;

	public:

		/// <summary>文字列の長さを返す</summary>
		/// <param name="str">文字列</param>
		static unsigned int Length(const String& str);

		/// <summary>stringクラスに変換</summary>
		/// <param name="str">文字列</param>
		static std::string ToNarrow(const String& str);

		/// <summary>wstringクラスに変換</summary>
		/// <param name="str">文字列</param>
		static std::wstring ToWide(const String& str);

		/// <summary>分割して返す</summary>
		/// <param name="str">文字列</param>
		/// <param name="delim">分割文字</param>
		/// <returns>分割して収納したリスト</returns>
		static std::vector<String> Split(const String& str, wchar_t delim);

	private:

		/// <summary>wstringクラス</summary>
		std::wstring m_str;
	};
}

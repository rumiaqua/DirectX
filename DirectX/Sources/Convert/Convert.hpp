# pragma once

# include <vector>

# include <sstream>

std::string ToMultibyte(const std::wstring& str);

std::wstring ToUnicode(const std::string& str);

std::string ToNarrow(const std::wstring& wide);

std::wstring ToWide(const std::string& narrow);

template <typename Type>
Type ToValue(const std::wstring& str)
{
	std::wstringstream ss { str };
	Type value;
	ss >> value;
	return value;
}

template <typename Type>
std::wstring ToStr(Type value)
{
	std::wstringstream ss;
	ss << value;
	return ss.str();
}

/// <summary>文字列を指定の文字で分割する</summary>
/// <param name="str">文字列</param>
/// <param name="delim">分割点の文字</param>
/// <returns>分割した文字列の入ったコンテナ</returns>
std::vector<std::wstring> Split(const std::wstring& str, char delim);

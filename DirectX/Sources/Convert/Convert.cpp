# include "Convert.hpp"

std::string ToMultibyte(const std::wstring& str)
{
	return std::string { str.begin(), str.end() };
}

std::wstring ToUnicode(const std::string& str)
{
	return std::wstring { str.begin(), str.end() };
}

/// <summary>文字列を指定の文字で分割する</summary>
/// <param name="str">文字列</param>
/// <param name="delim">分割点の文字</param>
/// <returns>分割した文字列の入ったコンテナ</returns>
std::vector<std::wstring> Split(const std::wstring& str, char delim)
{
	std::vector<std::wstring> res;
	UINT current = 0, found;

	while ((found = str.find_first_of(delim, current)) != std::wstring::npos)
	{
		res.push_back(std::wstring(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::wstring(str, current, str.size() - current));
	return res;
}

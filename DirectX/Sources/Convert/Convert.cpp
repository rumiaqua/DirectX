# include "Convert.hpp"

std::string ToMultibyte(const std::wstring& str)
{
	return std::string { str.begin(), str.end() };
}

std::wstring ToUnicode(const std::string& str)
{
	return std::wstring { str.begin(), str.end() };
}

std::string ToNarrow(const std::wstring& wide)
{
	int slength = wide.length() + 1;
	int len = WideCharToMultiByte(CP_ACP, 0U, wide.c_str(), wide.length(), 0, 0U, 0, 0);
	char* buffer = new char[len];
	WideCharToMultiByte(CP_ACP, 0U, wide.c_str(), wide.length(), buffer, len, 0, 0);
	std::string result(buffer);
	delete buffer;
	return result;
}

std::wstring ToWide(const std::string& narrow)
{
	int slength = narrow.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0U, narrow.c_str(), narrow.length(), 0, 0);
	wchar_t* buffer = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0U, narrow.c_str(), narrow.length(), buffer, len);
	std::wstring result(buffer);
	delete buffer;
	return result;
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

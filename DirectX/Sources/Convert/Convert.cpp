# include "Convert.hpp"

std::string ToNarrow(const std::wstring& wide)
{
	int len;
	int slength = (int)wide.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

std::wstring ToWide(const std::string& narrow)
{
	int len;
	int slength = (int)narrow.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
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

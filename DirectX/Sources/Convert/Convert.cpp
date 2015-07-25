# include "Convert.hpp"

std::string ToMultibyte(const std::wstring& str)
{
	return std::string { str.begin(), str.end() };
}

std::wstring ToUnicode(const std::string& str)
{
	return std::wstring { str.begin(), str.end() };
}

/// <summary>��������w��̕����ŕ�������</summary>
/// <param name="str">������</param>
/// <param name="delim">�����_�̕���</param>
/// <returns>��������������̓������R���e�i</returns>
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

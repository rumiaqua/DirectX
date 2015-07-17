# include "Convert.hpp"

std::string ToMultibyte(const std::wstring& str)
{
	return std::string { str.begin(), str.end() };
}

std::wstring ToUnicode(const std::string& str)
{
	return std::wstring { str.begin(), str.end() };
}

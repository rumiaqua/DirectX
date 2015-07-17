# pragma once

std::string ToMultibyte(const std::wstring& str);

std::wstring ToUnicode(const std::string& str);

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

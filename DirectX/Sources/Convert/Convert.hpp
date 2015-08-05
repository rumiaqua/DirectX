# pragma once

# include <vector>

# include <sstream>

template <typename Type>
Type ToValue(const String& str)
{
	std::wstringstream ss { str.ToWide() };
	Type value;
	ss >> value;
	return value;
}

template <typename Type>
String ToStr(Type value)
{
	std::wstringstream ss;
	ss << value;
	return ss.str();
}

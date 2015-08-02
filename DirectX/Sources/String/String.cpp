# include "String.hpp"

namespace aqua
{
	std::string ToNarrow(const std::wstring& wide)
	{
		int length = WideCharToMultiByte(
			CP_OEMCP, 0, wide.c_str(), -1, NULL, 0, NULL, NULL);
		char* buffer = new char[length];
		WideCharToMultiByte(
			CP_OEMCP, 0, wide.c_str(), -1, buffer, length, NULL, NULL);
		std::string result(buffer, buffer + length - 1);
		delete[] buffer;
		return result;
	}

	std::wstring ToWide(const std::string& narrow)
	{
		int length =
			MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[length];
		MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, buffer, length);
		std::wstring result(buffer, buffer + length - 1);
		delete[] buffer;
		return result;
	}

	String::String()
		: m_str()
	{

	}

	String::String(const char* str)
		: String(std::string(str))
	{

	}

	String::String(const wchar_t* str)
		: m_str(str)
	{

	}

	String::String(const std::string& str)
		: m_str(aqua::ToWide(str))
	{
		
	}

	String::String(const std::wstring& str)
		: m_str(str)
	{

	}

	String::operator const char*() const
	{
		return ToNarrow(m_str).c_str();
	}

	String::operator const wchar_t*() const
	{
		return m_str.c_str();
	}

	String& String::operator = (const String& str)
	{
		m_str = str.m_str;
		return *this;
	}

	wchar_t String::operator[](unsigned int index) const
	{
		return m_str[index];
	}

	unsigned int String::Length(const String& str)
	{
		return str.m_str.length();
	}

	std::string String::ToNarrow(const String& str)
	{
		return aqua::ToNarrow(str.m_str);
	}

	std::wstring String::ToWide(const String& str)
	{
		return str.m_str;
	}
	std::vector<String> String::Split(const String& str, wchar_t delim)
	{
		std::vector<String> res;

		UINT current = 0, found;

		const std::wstring buffer = String::ToWide(str);

		while ((found = buffer.find_first_of(delim, current)) != std::wstring::npos)
		{
			res.push_back(std::wstring(buffer, current, found - current));
			current = found + 1;
		}

		res.push_back(std::wstring(buffer, current, buffer.size() - current));
		return res;

	}
}

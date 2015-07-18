# pragma once

class Windows
{
private:

	Windows();
	Windows(const Windows&);

	Windows& operator = (const Windows&);

	static LRESULT CALLBACK WindowProcedure(
		HWND window, UINT message, WPARAM wparam, LPARAM lparam);

	static Windows& Instance();

public:

	virtual ~Windows();

	static void Initialize(const std::wstring& name, UINT width, UINT height);

	static HWND Handle();

	static UINT Width();

	static UINT Height();
private:

	TCHAR m_appname[256];

	UINT m_width;

	UINT m_height;

	HINSTANCE m_instance;

	HWND m_window;
};

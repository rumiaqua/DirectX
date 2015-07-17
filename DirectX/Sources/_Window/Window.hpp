# pragma once

class Window
{
private:

	Window();
	Window(const Window&);

	Window& operator = (const Window&);

	static LRESULT CALLBACK WindowProcedure(
		HWND window, UINT message, WPARAM wparam, LPARAM lparam);

	static Window& Instance();

public:

	virtual ~Window();

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

# include "Window.hpp"

# include "Convert/Convert.hpp"

# include <strsafe.h>

Window::Window()
	: m_appname()
	, m_width(0U)
	, m_height(0U)
	, m_instance(nullptr)
	, m_window(nullptr)
{

}

LRESULT CALLBACK Window::WindowProcedure(
	HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_KEYUP:
		{
			if (wparam == VK_ESCAPE)
			{
				DestroyWindow(window);
			}
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(window, &ps);
			EndPaint(window, &ps);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{

		}
		break;
	}

	return DefWindowProc(window, message, wparam, lparam);
}

Window& Window::Instance()
{
	static Window window;
	return window;
}

Window::~Window()
{
	UnregisterClass(m_appname, m_instance);
}

void Window::Initialize(const std::wstring& name, UINT width, UINT height)
{
	auto& instance = Window::Instance();

	instance.m_instance = GetModuleHandle(NULL);

	StringCchCopy(instance.m_appname, sizeof(instance.m_appname), name.c_str());

	instance.m_width = width;

	instance.m_height = height;

	// ウィンドウ情報
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window::WindowProcedure;
	wc.hInstance = instance.m_instance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = instance.m_appname;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		throw std::exception("ウィンドウの登録に失敗しました");
	}

	// ウィンドウサイズ
	RECT rc { 0, 0, instance.m_width, instance.m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウの生成
	instance.m_window = CreateWindow(
		instance.m_appname,
		TEXT("DirectX Sample Program"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		instance.m_instance,
		NULL);

	if (!instance.m_window)
	{
		throw std::exception("ウィンドウの生成に失敗しました");
	}

	ShowWindow(instance.m_window, SW_SHOWNORMAL);
}

HWND Window::Handle()
{
	return Instance().m_window;
}

UINT Window::Width()
{
	return Instance().m_width;
}

UINT Window::Height()
{
	return Instance().m_height;
}

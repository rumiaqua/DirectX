# pragma once

# include "Handle/Handle.hpp"

class Window
{
public:

	Window(TCHAR* appname, TCHAR* classname,  UINT width, UINT height);

	virtual ~Window();

	static LRESULT CALLBACK WindowProcedure(
		HWND wnd, UINT message, WPARAM wparam, LPARAM lparam);

private:

	void InitWindow();

	void InitDevice();

	void CreateDeviceAndSwapChain();

	void CreateRenderTargetView();

	void SetViewport();

	static Window& Instance();

public:

	static void Clear(float color[4]);

	static void Flip();

	static ID3D11Device* Device();

	static ID3D11DeviceContext* Context();

	static IDXGISwapChain* SwapChain();

	static D3D_DRIVER_TYPE DriverType();

	static UINT Width();

	static UINT Height();

private:

	TCHAR* m_appname;

	TCHAR* m_classname;

	UINT m_width;

	UINT m_height;

	HINSTANCE m_instance;

	HWND m_wnd;

	D3D_DRIVER_TYPE m_driverType;

	D3D_FEATURE_LEVEL m_featureLevel;

	Handle<ID3D11Device> m_device;

	Handle<ID3D11DeviceContext> m_context;

	Handle<IDXGISwapChain> m_swapChain;

	Handle<ID3D11RenderTargetView> m_renderTargetView;

	Handle<ID3D11Texture2D> m_depthStencil;;

	Handle<ID3D11DepthStencilView> m_depthStencilView;
};

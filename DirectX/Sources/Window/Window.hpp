# pragma once

# include "Handle/Handle.hpp"

class Window
{
public:

	Window(TCHAR* appname, UINT width, UINT height);	

	virtual ~Window();

	static LRESULT CALLBACK WindowProcedure(
		HWND wnd, UINT message, WPARAM wparam, LPARAM lparam);

private:

	void InitWindow();

	void InitDevice();

	void CreateDeviceAndSwapChain();

	void CreateRenderTargetView();

	void SetViewport();

public:

	void Clear(float color[4]);

	void Present();

	Reference<ID3D11Device> Device();

	Reference<ID3D11DeviceContext> Context();

private:

	TCHAR* m_appname;

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
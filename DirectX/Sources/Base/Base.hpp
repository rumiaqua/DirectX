# pragma once

# include "Handle/Handle.hpp"

class Base
{
private:

	Base();

	Base(const Base&);

	Base& operator = (const Base&);

private:

	static Base& Instance();

public:

	static void Initialize();

	static D3D_DRIVER_TYPE DriverType();

	static D3D_FEATURE_LEVEL FeatureLevel();

	static ID3D11Device* Device();

	static ID3D11DeviceContext* Context();

	static IDXGISwapChain* SwapChain();

	static void Clear(const float* color);

	static void Flip();

private:

	D3D_DRIVER_TYPE m_driverType;

	D3D_FEATURE_LEVEL m_featureLevel;

	Handle<ID3D11Device> m_device;

	Handle<ID3D11DeviceContext> m_context;

	Handle<IDXGISwapChain> m_swapChain;

	Handle<ID3D11RenderTargetView> m_renderTargetView;

	Handle<ID3D11Texture2D> m_depthStencil;

	Handle<ID3D11DepthStencilView> m_depthStencilView;
};

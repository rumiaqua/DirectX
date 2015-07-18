# include "Base.hpp"

# include "Handle/Handle.hpp"

# include "Windows/Windows.hpp"

Base::Base()
{
	Initialize();
}

Base& Base::Instance()
{
	static Base base;

	return base;
}

void Base::Initialize()
{
	HRESULT hr = S_OK;

	auto& instance = Instance();

	UINT createDeviceFlags = 0;
# if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
# endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 640;
	swapChainDesc.BufferDesc.Height = 480;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = Windows::Handle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// デバイスとスワップチェインを生成
	for (UINT i = 0; i < numDriverTypes; ++i)
	{
		instance.m_driverType = driverTypes[i];

		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			instance.m_driverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&instance.m_swapChain,
			&instance.m_device,
			&instance.m_featureLevel,
			&instance.m_context);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
		throw std::exception("デバイスとスワップチェインの生成に失敗しました");
	}

	// バックバッファの取得
	Handle<ID3D11Texture2D> backBuffer;
	hr = instance.m_swapChain->GetBuffer(
		0U, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (FAILED(hr))
	{
		throw std::exception("バックバッファの取得に失敗しました");
	}

	// レンダーターゲットビューを生成
	hr = instance.m_device->CreateRenderTargetView(
		backBuffer, NULL, &instance.m_renderTargetView);
	if (FAILED(hr))
	{
		throw std::exception("レンダーターゲットビューの生成に失敗しました");
	}

	// 深度ステンシルの生成
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = Windows::Width();
	depthDesc.Height = Windows::Height();
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;
	hr = instance.m_device->CreateTexture2D(
		&depthDesc, NULL, &instance.m_depthStencil);
	if (FAILED(hr))
	{
		throw std::exception("深度ステンシルの生成に失敗しました");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = depthDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = instance.m_device->CreateDepthStencilView(
		instance.m_depthStencil, &dsvDesc, &instance.m_depthStencilView);

	// 出力マネージャにレンダーターゲットビューを設定
	instance.m_context->OMSetRenderTargets(
		1, &instance.m_renderTargetView, instance.m_depthStencilView);

	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)Windows::Width();
	viewport.Height = (FLOAT)Windows::Height();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	instance.m_context->RSSetViewports(1, &viewport);
}

D3D_DRIVER_TYPE Base::DriverType()
{
	return Instance().m_driverType;
}

D3D_FEATURE_LEVEL Base::FeatureLevel()
{
	return Instance().m_featureLevel;
}

ID3D11Device* Base::Device()
{
	return Instance().m_device;
}

ID3D11DeviceContext* Base::Context()
{
	return Instance().m_context;
}

IDXGISwapChain* Base::SwapChain()
{
	return Instance().m_swapChain;
}

void Base::Clear(const float color[4])
{
	Instance().m_context->ClearRenderTargetView(
		Instance().m_renderTargetView, color);

	Instance().m_context->ClearDepthStencilView(
		Instance().m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0U);
}

void Base::Flip()
{
	Instance().m_swapChain->Present(0U, 0U);
}
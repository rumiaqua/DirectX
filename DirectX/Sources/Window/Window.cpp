# include "Window.hpp"

Window::Window(TCHAR* appname, TCHAR* classname, UINT width, UINT height)
	: m_appname(appname)
	, m_classname(classname)
	, m_width(width)
	, m_height(height)
	, m_instance()
	, m_wnd()
	, m_driverType()
	, m_featureLevel()
	, m_device()
	, m_context()
	, m_swapChain()
	, m_renderTargetView()
{
	m_instance = GetModuleHandle(NULL);

	InitWindow();
	
	InitDevice();
}

Window::~Window()
{
	if (m_context)
	{
		m_context->ClearState();
	}

	UnregisterClass(m_classname, m_instance);
}

LRESULT CALLBACK Window::WindowProcedure(
	HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_KEYUP:
		{
			if (wparam == VK_ESCAPE)
			{
				DestroyWindow(wnd);
			}
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(wnd, &ps);
			EndPaint(wnd, &ps);
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

	return DefWindowProc(wnd, message, wparam, lparam);
}

void Window::InitWindow()
{
	// �g���E�B���h�E�N���X�̓o�^
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window::WindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_instance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_classname;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		throw std::exception("�E�B���h�E�̓o�^�Ɏ��s���܂���");
	}

	// �E�B���h�E�T�C�Y�̐ݒ�
	RECT rc = { 0, 0, m_width, m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̐���
	m_wnd = CreateWindow(
		m_classname,
		m_appname,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		m_instance,
		NULL);

	if (!m_wnd)
	{
		throw std::exception("�E�B���h�E�̐����Ɏ��s���܂���");
	}

	// �E�B���h�E�̕\���ݒ�
	ShowWindow(m_wnd, SW_SHOWNORMAL);
}

void Window::InitDevice()
{
	CreateDeviceAndSwapChain();

	CreateRenderTargetView();

	SetViewport();

	// �v���~�e�B�u�̎�ނ�ݒ�
	m_context->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Window::CreateDeviceAndSwapChain()
{
	HRESULT hr;
	
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// �h���C�o�[�^�C�v
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// �X���b�v�`�F�C���̐ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_width;
	sd.BufferDesc.Height = m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_wnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	// �f�o�C�X�ƃX���b�v�`�F�C�����쐬����
	for (UINT idx = 0; idx < numDriverTypes; idx++)
	{
		m_driverType = driverTypes[idx];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			m_driverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_swapChain,
			&m_device,
			&m_featureLevel,
			&m_context);

		if (SUCCEEDED(hr))
		{
			// ���������烋�[�v�E�o
			break;
		}
	}
	if (FAILED(hr))
	{
		// �쐬�Ɏ��s������I��
		throw std::exception("�f�o�C�X�ƃX���b�v�`�F�C���̐����Ɏ��s���܂���");
	}
}

void Window::CreateRenderTargetView()
{
	// �o�b�N�o�b�t�@�擾
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT hr = m_swapChain->GetBuffer(
		0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		throw std::exception("�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���");
	}

	// �����_�[�^�[�Q�b�g�r���[�𐶐�
	hr = m_device->CreateRenderTargetView(
		pBackBuffer, NULL, &m_renderTargetView);
	pBackBuffer->Release();
	pBackBuffer = NULL;
	if (FAILED(hr))
	{
		throw std::exception("�����_�[�^�[�Q�b�g�r���[�̐����Ɏ��s���܂���");
	}

	// �[�x�X�e���V���̍쐬
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = m_width;
	depthDesc.Height = m_height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;
	hr = m_device->CreateTexture2D(
		&depthDesc, NULL, &m_depthStencil);
	if (FAILED(hr))
	{
		throw std::exception("�[�x�X�e���V���̐����Ɏ��s���܂���");
	}

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = depthDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = m_device->CreateDepthStencilView(
		m_depthStencil, &dsvDesc, &m_depthStencilView);

	// �o�̓}�l�[�W���Ƀ����_�[�^�[�Q�b�g�r���[��ݒ�
	m_context->OMSetRenderTargets(
		1, &m_renderTargetView, m_depthStencilView);
}

void Window::SetViewport()
{
	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_width;
	vp.Height = (FLOAT)m_height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_context->RSSetViewports(1, &vp);
}

Window& Window::Instance()
{
	static Window window { L"Static Instance Window", L"DirectX HOGE", 640, 480 };
	return window;
}

void Window::Clear(float color[4])
{
	auto& instance = Instance();

	instance.m_context->ClearRenderTargetView(
		instance.m_renderTargetView, color);

	instance.m_context->ClearDepthStencilView(
		instance.m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Window::Flip()
{
	auto& instance = Instance();

	instance.m_swapChain->Present(0, 0);
}

ID3D11Device* Window::Device()
{
	return Instance().m_device;
}

ID3D11DeviceContext* Window::Context()
{
	return Instance().m_context;
}

IDXGISwapChain* Window::SwapChain()
{
	return Instance().m_swapChain;
}

D3D_DRIVER_TYPE Window::DriverType()
{
	return Instance().m_driverType;
}

UINT Window::Width()
{
	return Instance().m_width;
}

UINT Window::Height()
{
	return Instance().m_height;
}

float Window::Aspect()
{
	return (FLOAT)Window::Width() / (FLOAT)Window::Height();
}

# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# define ISVALID(VAR) if(!(VAR)->IsValid())

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3D11SamplerState> sampler;

Matrix world;

Matrix view;

Matrix projection;

Float4 color;

Model player;

static float t = 0.0f;

using namespace DirectX;

void Initialize()
{
	HRESULT hr = S_OK;

	auto device = Window::Device();

	auto context = Window::Context();

	Shader::SetEffect(L"Contents/Tutorial07.fx");

	// Shader::Tech(L"Default");
	Shader::Tech(L"Color");

	Shader::Pass(L"P0");

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	Shader::InputLayout(layout, ARRAYSIZE(layout));

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&sampDesc, &sampler);
	if (FAILED(hr))
	{
		return;
	}

	world = XMMatrixIdentity();
	Shader::SetMatrix(L"World", world);

	view = XMMatrixLookAtLH(
		Float4(0.0f, 3.0f, -6.0f, 0.0f).ToVector(),
		Float4(0.0f, 0.0f, 0.0f, 0.0f).ToVector(),
		Float4(0.0f, 1.0f, 0.0f, 0.0f).ToVector());
	Shader::SetMatrix(L"View", view);

	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, 4.0f / 3.0f, 1.0f, 250.0f);
	Shader::SetMatrix(L"Projection", projection);


	TexMetadata metadata;
	ScratchImage image;
	hr = LoadFromDDSFile(L"Contents/seafloor.dds", 0U, &metadata, image);
	if (FAILED(hr))
	{
		return;
	}
	hr = CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&shaderResourceView);
	if (FAILED(hr))
	{
		return;
	}

	Shader::SetShaderResource(L"txDiffuse", shaderResourceView);

	Shader::SetSampler(L"samLinear", 0, sampler);

	Shader::SetVector(L"lightPosition", Float4(0.0f, 0.0f, -10.0f, 0.0f));

	player.Load(L"Contents/Box.obj");
}

void Update()
{
	if (Window::DriverType() == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static WORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
		{
			dwTimeStart = dwTimeCur;
		}
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	static Float3 velocity;

	static float angle = 0.0f;

	static float oneRadian = XM_PI / 180.0f;

	static const float deltaTime = 0.016667f;

	static const Float3 Forward = { 0.0f, 0.0f, 1.0f };

	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		angle -= oneRadian * deltaTime;
	}

	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		angle += oneRadian * deltaTime;
	}

	if (GetAsyncKeyState('A') != 0)
	{
		velocity.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('D') != 0)
	{
		velocity.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('W') != 0)
	{
		velocity.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('S') != 0)
	{
		velocity.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('E') != 0)
	{
		velocity.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('X') != 0)
	{
		velocity.y -= 0.1f * deltaTime;
	}

	static Float3 camera { 0.0f, 3.0f, -6.0f };
	if (GetAsyncKeyState('J') != 0)
	{
		camera.x -= 0.1f * deltaTime;
	}
	if (GetAsyncKeyState('L') != 0)
	{
		camera.x += 0.1f * deltaTime;
	}
	if (GetAsyncKeyState('I') != 0)
	{
		camera.z += 0.1f * deltaTime;
	}
	if (GetAsyncKeyState('K') != 0)
	{
		camera.z -= 0.1f * deltaTime;
	}
	if (GetAsyncKeyState('O') != 0)
	{
		camera.y += 0.1f * deltaTime;
	}
	if (GetAsyncKeyState(',') != 0)
	{
		camera.y -= 0.1f * deltaTime;
	}

	view = XMMatrixLookAtLH(
		Float3(camera.x, camera.y, camera.z).ToVector(0.0f),
		Float3(velocity.x, velocity.y, velocity.z).ToVector(0.0f),
		Float3(0.0f, 1.0f, 0.0f).ToVector(0.0f));
	Shader::SetMatrix(L"View", view);

	// å∏êä
	// velocity.x *= 0.99f;
	// velocity.z *= 0.99f;

	Matrix rotate = XMMatrixRotationY(angle);
	// rotate = XMMatrixRotationRollPitchYaw(t * 3, t * 1, t * 2);
	Matrix translate = XMMatrixTranslation(velocity.x, velocity.y, velocity.z);

	world = rotate * translate;

	Shader::SetMatrix(L"World", world);
}

void Render()
{
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	Window::Clear(clearColor);

	Shader::SetMatrix(L"World", world);

	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
	color.w = 1.0f;
	Shader::SetVector(L"vMeshColor", color);

	Matrix worldView = world * view;

	XMVECTOR det;
	Matrix worldViewInverse = XMMatrixInverse(&det, worldView);
	Matrix worldViewInverseTranspose =
		XMMatrixTranspose(worldViewInverse);

	Shader::SetMatrix(L"worldView", worldView);

	Shader::SetMatrix(L"worldViewInverseTranspose", worldViewInverseTranspose);

	Shader::Apply();

	player.Render();

	Window::Flip();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Initialize();

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}
}

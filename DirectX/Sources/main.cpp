# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3D11ShaderResourceView> soccerballTexture;

Handle<ID3D11ShaderResourceView> texture2D;

Handle<ID3D11SamplerState> sampler;

Matrix world;

Matrix view;

Matrix projection;

Float4 color;

Model player;

Model enemy;

Float3 playerPosition;

Float3 enemyPosition;

Texture2D texture;

static float t = 0.0f;

using namespace DirectX;

void Initialize()
{
	HRESULT hr = S_OK;

	auto device = Window::Device();

	auto context = Window::Context();

	Shader::AddShader(L"Default", L"Contents/Tutorial07.fx");

	Shader::Change(L"Default");

	Shader::Tech(L"Default");

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
		XM_PIDIV4, 4.0f / 3.0f, 0.1f, 100.0f);
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

	hr = LoadFromTGAFile(L"Contents/oldball.tga", &metadata, image);
	if (FAILED(hr))
	{
		return;
	}
	hr = CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&soccerballTexture);
	if (FAILED(hr))
	{
		return;
	}

	hr = LoadFromWICFile(L"Contents/panda_big.png", 0U, &metadata, image);
	if (FAILED(hr))
	{
		return;
	}
	hr = CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&texture2D);
	if (FAILED(hr))
	{
		return;
	}

	Shader::SetShaderResource(L"txDiffuse", shaderResourceView);

	Shader::SetSampler(L"samLinear", 0, sampler);

	player.Box();

	enemy.Plane();

	// Tutorial07_2 シェーダー読込
	Shader::AddShader(L"NoChangeColor", L"Contents/Tutorial07_2.fx");

	Shader::Change(L"NoChangeColor");

	Shader::Tech(L"Default");

	Shader::Pass(L"P0");

	texture.Load(L"Contents/panda.png");

	// Texture シェーダー読込
	Shader::AddShader(L"Texture", L"Contents/Texture.fx");
	Shader::Change(L"Texture");
	Shader::Tech(L"Default");
	Shader::Pass(L"P0");
	Shader::SetSampler(L"samLinear", 0, sampler);

	// シェーダーのセット
	Shader::Change(L"Default");
}

void Update()
{
	if (Window::DriverType() == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
		{
			dwTimeStart = dwTimeCur;
		}
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

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

	// player
	if (GetAsyncKeyState('A') != 0)
	{
		playerPosition.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('D') != 0)
	{
		playerPosition.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('W') != 0)
	{
		playerPosition.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('S') != 0)
	{
		playerPosition.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('E') != 0)
	{
		playerPosition.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('X') != 0)
	{
		playerPosition.y -= 0.1f * deltaTime;
	}

	// enemy
	if (GetAsyncKeyState('F') != 0)
	{
		enemyPosition.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('H') != 0)
	{
		enemyPosition.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('T') != 0)
	{
		enemyPosition.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('G') != 0)
	{
		enemyPosition.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('Y') != 0)
	{
		enemyPosition.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('B') != 0)
	{
		enemyPosition.y -= 0.1f * deltaTime;
	}
}

void Render()
{
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	Window::Clear(clearColor);

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

	// player render
	Shader::Change(L"NoChangeColor");

	Matrix mat = XMMatrixTranslation(playerPosition.x, playerPosition.y, playerPosition.z);
	mat = XMMatrixRotationY(t) * mat;
	Shader::SetMatrix(L"World", mat);
	Shader::SetMatrix(L"View", view);
	Shader::SetMatrix(L"Projection", projection);
	Shader::SetShaderResource(L"txDiffuse", soccerballTexture);
	Shader::SetSampler(L"samLinear", 0, sampler);
	Shader::Apply();

	player.Render();

	// enemy render
	Shader::Change(L"Default");
	Shader::SetMatrix(L"World", XMMatrixTranslation(enemyPosition.x, enemyPosition.y, enemyPosition.z));
	Shader::SetMatrix(L"View", view);
	Shader::SetMatrix(L"Projection", projection);
	Shader::SetVector(L"vMeshColor", color);
	Shader::Apply();

	enemy.Render();

	// texture render
	texture.Render();

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
			continue;
		}

		Update();
		Render();
	}
}

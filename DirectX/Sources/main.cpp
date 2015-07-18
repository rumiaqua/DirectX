# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# define ISVALID(VAR) if(!(VAR)->IsValid())

Handle<ID3D11ShaderResourceView> shaderResourceView;

ID3DX11Effect* effect;

ID3DX11EffectTechnique* technique;

ID3DX11EffectPass* pass;

Handle<ID3D11InputLayout> vertexLayout;

Handle<ID3D11SamplerState> sampler;

Matrix world;

Matrix view;

Matrix projection;

Float4 color;

Model player;

using namespace DirectX;

void Initialize()
{
	HRESULT hr = S_OK;

	auto device = Window::Device();

	auto context = Window::Context();

	/*hr = D3DX11CompileEffectFromFile(
		L"Contents/Tutorial07.fx",
		NULL,
		NULL,
		0U,
		0U,
		device,
		&effect,
		NULL);
	if (FAILED(hr))
	{
		return;
	}*/

	Shader::SetEffect(L"Contents/Tutorial07.fx");
	effect = Shader::Effect();

	technique = effect->GetTechniqueByName("Default");
	if (!technique->IsValid())
	{
		return;
	}

	pass = technique->GetPassByName("P0");
	if (!pass->IsValid())
	{
		return;
	}

	D3DX11_PASS_DESC passDesc;
	pass->GetDesc(&passDesc);
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		&vertexLayout);
	if (FAILED(hr))
	{
		return;
	}

	context->IASetInputLayout(vertexLayout);

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

	// Shader::SetEffect(effect);

	world = XMMatrixIdentity();
	Shader::Variable(L"World")->AsMatrix()->SetMatrix(world);

	view = XMMatrixLookAtLH(
		Float4(0.0f, 3.0f, -6.0f, 0.0f).ToVector(),
		Float4(0.0f, 0.0f, 0.0f, 0.0f).ToVector(),
		Float4(0.0f, 1.0f, 0.0f, 0.0f).ToVector());
	Shader::Variable(L"View")->AsMatrix()->SetMatrix(view);

	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, 4.0f / 3.0f, 1.0f, 250.0f);
	Shader::Variable(L"Projection")->AsMatrix()->SetMatrix(projection);


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

	Shader::Variable(L"txDiffuse")->AsShaderResource()->SetResource(shaderResourceView);

	Shader::Variable(L"samLinear")->AsSampler()->SetSampler(0, sampler);

	Shader::Variable(L"lightPosition")->AsVector()->SetFloatVector(
		Float4(0.0f, 0.0f, -10.0f, 0.0f));

	player.Load(L"Contents/Box.obj");
}

void Update()
{
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

	// Œ¸Š
	// velocity.x *= 0.99f;
	// velocity.z *= 0.99f;

	Matrix rotate = XMMatrixRotationY(angle);
	Matrix translate = XMMatrixTranslation(velocity.x, velocity.y, velocity.z);

	world = rotate * translate;

	Shader::Variable(L"World")->AsMatrix()->SetMatrix(world);
}

void Render()
{
	static float t = 0.0f;
	t += (float)XM_PI * 0.0125f;

	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	static float clearColor[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	Window::Clear(clearColor);

	Shader::Variable(L"World")->AsMatrix()->SetMatrix(world);

	Shader::Variable(L"vMeshColor")->AsVector()->SetFloatVector(color);

	Matrix worldView = world * view;

	XMVECTOR det;
	Matrix worldViewInverse = XMMatrixInverse(&det, worldView);
	Matrix worldViewInverseTranspose =
		XMMatrixTranspose(worldViewInverse);

	Shader::Variable(L"worldView")->AsMatrix()->SetMatrix(worldView);

	Shader::Variable(L"worldViewInverseTranspose")->AsMatrix()->SetMatrix(
		worldViewInverseTranspose);

	pass->Apply(0, Window::Context());

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

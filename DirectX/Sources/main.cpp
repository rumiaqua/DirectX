# include "Window/Window.hpp"

# include "Model/Model.hpp"

# define ISVALID(VAR) if(!(VAR)->IsValid())

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3DX11Effect> effect;

ID3DX11EffectTechnique* technique;

ID3DX11EffectPass* pass;

Handle<ID3D11InputLayout> vertexLayout;

Handle<ID3D11SamplerState> sampler;

ID3DX11EffectMatrixVariable* worldVariable;

ID3DX11EffectMatrixVariable* viewVariable;

ID3DX11EffectMatrixVariable* projectionVariable;

ID3DX11EffectMatrixVariable* worldViewVariable;

ID3DX11EffectMatrixVariable* worldViewInverseTransposeVariable;

ID3DX11EffectVectorVariable* colorVariable;

ID3DX11EffectSamplerVariable* samplerVariable;

ID3DX11EffectShaderResourceVariable* textureVariable;

ID3DX11EffectVectorVariable* lightPositionVariable;

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

	hr = D3DX11CompileEffectFromFile(
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
	}

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

	worldVariable = effect->GetVariableByName("World")->AsMatrix();
	if (!worldVariable->IsValid())
	{
		return;
	}

	viewVariable = effect->GetVariableByName("View")->AsMatrix();
	if (!viewVariable->IsValid())
	{
		return;
	}

	projectionVariable = effect->GetVariableByName("Projection")->AsMatrix();
	if (!projectionVariable->IsValid())
	{
		return;
	}

	worldViewVariable = effect->GetVariableByName("worldView")->AsMatrix();
	if (!worldViewVariable->IsValid())
	{
		return;
	}

	worldViewInverseTransposeVariable = effect->GetVariableByName("worldViewInverseTranspose")->AsMatrix();
	if (!worldViewInverseTransposeVariable->IsValid())
	{
		return;
	}

	colorVariable = effect->GetVariableByName("vMeshColor")->AsVector();
	if (!colorVariable->IsValid())
	{
		return;
	}

	samplerVariable = effect->GetVariableByName("samLinear")->AsSampler();
	if (!samplerVariable->IsValid())
	{
		return;
	}

	textureVariable = effect->GetVariableByName("txDiffuse")->AsShaderResource();
	if (!textureVariable->IsValid())
	{
		return;
	}

	lightPositionVariable = effect->GetVariableByName("lightPosition")->AsVector();
	if (!lightPositionVariable->IsValid())
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

	world = XMMatrixIdentity();
	worldVariable->SetMatrix(world);

	view = XMMatrixLookAtLH(
		Float4(0.0f, 3.0f, -6.0f, 0.0f).ToVector(),
		Float4(0.0f, 0.0f, 0.0f, 0.0f).ToVector(),
		Float4(0.0f, 1.0f, 0.0f, 0.0f).ToVector());
	viewVariable->SetMatrix(view);

	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, 4.0f / 3.0f, 1.0f, 250.0f);
	projectionVariable->SetMatrix(projection);


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

	textureVariable->SetResource(shaderResourceView);

	samplerVariable->SetSampler(0, sampler);

	lightPositionVariable->SetFloatVector(
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

	worldVariable->SetMatrix(world);
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

	worldVariable->SetMatrix(world);

	colorVariable->SetFloatVector(color);

	Matrix worldView = world * view;

	XMVECTOR det;
	Matrix worldViewInverse = XMMatrixInverse(&det, worldView);
	Matrix worldViewInverseTranspose =
		XMMatrixTranspose(worldViewInverse);

	worldViewVariable->SetMatrix(worldView);

	worldViewInverseTransposeVariable->SetMatrix(
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

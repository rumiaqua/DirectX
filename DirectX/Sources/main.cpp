# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "LoadOBJ.hpp"

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

ID3DX11EffectMatrixVariable* modelVariable;

Matrix world;

Matrix view;

Matrix projection;

Float4 color;

Model player;

Matrix model;

using namespace DirectX;

void Initialize(Window& window)
{
	HRESULT hr = S_OK;

	auto device = window.Device();

	auto context = window.Context();

	technique = effect->GetTechniqueByName("Default");

	pass = technique->GetPassByName("P0");

	D3DX11_PASS_DESC passDesc;
	pass->GetDesc(&passDesc);
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		&vertexLayout);

	worldVariable = effect->GetVariableByName("World")->AsMatrix();

	viewVariable = effect->GetVariableByName("View")->AsMatrix();

	projectionVariable = effect->GetVariableByName("Projection")->AsMatrix();

	worldViewVariable = effect->GetVariableByName("worldView")->AsMatrix();

	worldViewInverseTransposeVariable = effect->GetVariableByName("worldViewInverseTranspose")->AsMatrix();

	colorVariable = effect->GetVariableByName("vMeshColor")->AsVector();

	samplerVariable = effect->GetVariableByName("samLinear")->AsSampler();

	textureVariable = effect->GetVariableByName("txDiffuse")->AsShaderResource();

	lightPositionVariable = effect->GetVariableByName("lightPosition")->AsVector();

	modelVariable = effect->GetVariableByName("Model")->AsMatrix();

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
	device->CreateSamplerState(&sampDesc, &sampler);

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
	LoadFromDDSFile(L"Contents/seafloor.dds", 0U, &metadata, image);
	CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&shaderResourceView);

	D3DX11CompileEffectFromFile(
		L"Contents/Tutorial07.fx",
		NULL,
		NULL,
		0U,
		0U,
		device,
		&effect,
		NULL);

	textureVariable->SetResource(shaderResourceView);

	samplerVariable->SetSampler(0, sampler);

	lightPositionVariable->SetFloatVector(
		Float4(0.0f, 0.0f, -10.0f, 0.0f));

	player.Load(L"Contents/Box.obj", device);

	model = XMMatrixIdentity();
	modelVariable->SetMatrix(model);
}


void Update(Window& window)
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

void Render(Window& window)
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
	window.Clear(clearColor);

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

	pass->Apply(0, window.Context());

	player.Render(window.Context());

	window.Present();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window { L"Direct X Project", 640, 480 };

	Initialize(window);

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
			Update(window);
			Render(window);
		}
	}
}

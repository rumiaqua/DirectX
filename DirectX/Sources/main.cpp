# include "Window/Window.hpp"

// # include "_Window/Window.hpp"

// # include "Base/Base.hpp"

# include "Model/Model.hpp"

# include "Texture2D/Texture2D.hpp"

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

// Texture2D texture2D;
Model texture2D;

using namespace DirectX;

void Initialize(Window& window)
{
	// Window::Initialize(L"Direct X Project", 640, 480);

	// Base::Initialize();

	HRESULT hr = S_OK;

	TexMetadata metadata;
	ScratchImage image;
	LoadFromDDSFile(L"Contents/seafloor.dds", 0U, &metadata, image);
	CreateShaderResourceView(
		window.Device(),
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
		window.Device(),
		&effect,
		NULL);

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
	window.Device()->CreateInputLayout(
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

	window.Context()->IASetInputLayout(vertexLayout);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	window.Device()->CreateSamplerState(&sampDesc, &sampler);

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

	textureVariable->SetResource(shaderResourceView);

	samplerVariable->SetSampler(0, sampler);

	lightPositionVariable->SetFloatVector(
		Float4(0.0f, 0.0f, 10.0f, 0.0f));

	// player.Load(L"Contents/Box.obj");
	player.Load(L"Contents/Casual_Man.obj");

	texture2D.Texture();
}


void Update()
{
	static Float3 velocity;

	static float angle = 0.0f;

	static float oneRadian = XM_PI / 180.0f;

	static const float deltaTime = 0.016667f;

	static const Float3 Forward = { 0.0f, 0.0f, 1.0f };

	if (GetAsyncKeyState('A') != 0)
	{
		angle -= oneRadian * deltaTime;
	}

	if (GetAsyncKeyState('D') != 0)
	{
		angle += oneRadian * deltaTime;
	}

	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		velocity.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		velocity.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState(VK_UP) != 0)
	{
		velocity.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		velocity.z -= 0.1f * deltaTime;
	}

	// 減衰
	// velocity.x *= 0.99f;
	// velocity.z *= 0.99f;

	Matrix rotate = XMMatrixRotationY(angle);

	// 回転方向へ指定ベクトル量移動

	Float3 forward = XMVector3Transform(velocity.ToVector(), rotate);

	Matrix translate = XMMatrixTranslation(forward.x, forward.y, forward.z);

	world = rotate * translate;

	worldVariable->SetMatrix(world);

	/*
	float angle = 0.0f;

	static float oneRadian = XM_PI / 180.0f / 60.0f;

	if (GetAsyncKeyState('A') != 0)
	{
		angle -= oneRadian;
	}
	if (GetAsyncKeyState('D') != 0)
	{
		angle += oneRadian;
	}

	// 回転行列
	Matrix rotate = XMMatrixRotationY(angle);

	// 移動
	static Float3 velocity;

	if (GetAsyncKeyState(VK_SPACE) != 0)
	{
		velocity.y = 0.005f;
	}

	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		velocity.x -= 0.001f;
	}

	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		velocity.x += 0.001f;
	}

	if (GetAsyncKeyState(VK_UP) != 0)
	{
		velocity.z += 0.001f;
	}

	if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		velocity.z -= 0.001f;
	}

	// x速度クランプ
	auto xsign = velocity.x / std::abs(velocity.x);
	velocity.x = std::abs(velocity.x) > 0.005f ? 0.005f * xsign : velocity.x;
	velocity.x *= 0.995f;

	// z速度クランプ
	auto zsign = velocity.z / std::abs(velocity.z);
	velocity.z = std::abs(velocity.z) > 0.005f ? 0.005f * zsign : velocity.z;
	velocity.z *= 0.995f;

	// 重力
	velocity.y -= 0.000005f;

	// 平行移動行列
	Matrix translate = XMMatrixTranslation(velocity.x, velocity.y, velocity.z);

	// 拡大縮小行列
	Matrix scale = XMMatrixIdentity();

	// 合成行列
	Matrix composition = rotate * translate;

	// 行列をかける
	world = composition;

	// y座標制御
	world.m42 = world.m42 < -3.0f ? -3.0f : world.m42;

	worldVariable->SetMatrix(world);

	modelVariable->SetMatrix(model);
	*/
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

	// 通常の透視射影描画
	worldVariable->SetMatrix(world);
	viewVariable->SetMatrix(view);
	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, 4.0f / 3.0f, 1.0f, 250.0f);
	projectionVariable->SetMatrix(projection);
	pass->Apply(0, window.Context());
	// player.Render(window.Context());

	// 2D正射影
	worldVariable->SetMatrix((float*)XMMatrixIdentity().m);
	viewVariable->SetMatrix((float*)XMMatrixIdentity().m);
	projection.m11 = 2.0f / 640.0f;
	projection.m12 = 0.0f;
	projection.m13 = 0.0f;
	projection.m14 = 0.0f;
	projection.m21 = 0.0f;
	projection.m22 = -2.0f / 480.0f;
	projection.m23 = 0.0f;
	projection.m24 = 0.0f;
	projection.m31 = 0.0f;
	projection.m32 = 0.0f;
	projection.m33 = 1.0f;
	projection.m34 = 0.0f;
	projection.m41 = -1.0f;
	projection.m42 = 1.0f;
	projection.m43 = 0.0f;
	projection.m44 = 1.0f;
	projectionVariable->SetMatrix(projection);

	Matrix model = XMMatrixIdentity();
	model = model * XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 3.14f / 4.0f);
	model = model * XMMatrixScaling(150.0f, 150.0f, 1.0f);
	model = model * XMMatrixTranslation(320.0f, 240.0f, 0.0f);
	worldVariable->SetMatrix(
		(float*)model.m);

	// pass->Apply(0, Base::Context());
	pass->Apply(0, window.Context());

	texture2D.Render();

	// Base::Flip();
	window.Present();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window { L"DirectX Sample Program", 640, 480 };

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
			Update();
			Render(window);
		}
	}
}

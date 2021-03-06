# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

# include "OrderedRender/OrderedRender.hpp"

# include "Convert/Convert.hpp"

# include "RenderObject/RenderPlayer.hpp"

# include "RenderObject/RenderEnemy.hpp"

# include "RenderObject/RenderTempObject.hpp"

# include "Resources/Resources.hpp"

# include "Resources/Texture.hpp"

# include "Stopwatch/Stopwatch.hpp"

# include <iostream>

# include <chrono>

# pragma comment (lib, "winmm.lib")

using namespace aqua;

using namespace DirectX;

Handle<ID3D11SamplerState> sampler;

Vector3 eye;

Vector3 at;

Vector3 up;

Matrix view;

Matrix projection;

static float t = 0.0f;

static const float deltaTime = 0.016667f;

std::shared_ptr<RenderTempObject> temp;

void Initialize()
{
	HRESULT hr = S_OK;

	auto device = Window::Device();

	auto context = Window::Context();

	// 変数初期化
	temp = std::make_shared<RenderTempObject>(view, projection);

	// シェーダーリソースビュー
	/*TexMetadata metadata;
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
	}*/

	// テクスチャリソースの読込
	Resources::Register<Texture>(L"seafloor", L"Contents/seafloor.dds");
	Resources::Register<Texture>(L"panda", L"Contents/panda.png");

	// サンプラーステート
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

	// 視点座標
	eye = Vector3(0.0f, 3.0f, -6.0f);

	// 注視点座標
	at = Vector3(0.0f, 0.0f, 0.0f);

	// 上方向ベクトル
	up = Vector3(0.0f, 1.0f, 0.0f);

	// ビュー行列
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));

	// 透視射影行列
	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, Window::Aspect(), 0.1f, 250.0f);

	// シェーダーのセット

	// デフォルトシェーダー
	Shader::AddShader(L"Default", L"Contents/Shader/DefaultShader.hlsl");
	// シェーダーの切り替え
	Shader::Change(L"Default");
	// テクニックの指定
	Shader::Technique(L"Default");
	// サンプラーステート
	Shader::SetSampler(L"samplerState", 0, sampler);
	// シェーダーリソースビュー
	Shader::SetShaderResource(L"texture2d", Resources::Get<Texture>(L"panda")->ShaderResourceView());

	// 入力レイアウトの登録
	Shader::RegistInputLayout();
};

// 時間経過
void TimeElapsed()
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
}

// 視点移動
void EyeMove()
{
	if (GetAsyncKeyState('J') != 0)
	{
		eye.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('L') != 0)
	{
		eye.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('I') != 0)
	{
		eye.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('K') != 0)
	{
		eye.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('O') != 0)
	{
		eye.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('M') != 0)
	{
		eye.y -= 0.1f * deltaTime;
	}
}

// ビュー行列の更新
void ViewMatrix()
{
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));
}

// 更新
void Update()
{
	// Window::Update();

	TimeElapsed();

	temp->Update();

	EyeMove();
	ViewMatrix();
}

// 描画
void Render()
{
	// 背景色クリア
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.5f, 1.0f,
	};
	Window::Clear(clearColor);

	temp->Render();

	OrderedRender::Render();

	Window::Flip();
}

// int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
int main()
{
	using namespace std::chrono;

	try
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
	catch (std::exception& ex)
	{
		MessageBox(
			NULL,
			String(ex.what()),
			L"例外をキャッチしました",
			MB_OK);
	}
}

# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

# include "OrderedRender/OrderedRender.hpp"

# include "Convert/Convert.hpp"

# include "Vector2/Vector2.hpp"

# include "Vector3/Vector3.hpp"

# include "Vector4/Vector4.hpp"

# include "Matrix/Matrix.hpp"

using namespace aqua;

using namespace DirectX;

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3D11SamplerState> sampler;

Vector3 eye;
Vector3 at;
Vector3 up;

Matrix view;

Matrix projection;

Vector4 color;

Vector4 diffuseMaterial;

Matrix playerRotation;
Vector3 playerPosition;

Matrix enemyRotation;
Vector3 enemyPosition;

std::shared_ptr<aqua::Polygon> player;

std::shared_ptr<aqua::Polygon> enemy;

std::shared_ptr<aqua::Polygon> back;

std::shared_ptr<aqua::Polygon> texture;

static float t = 0.0f;

static float oneRadian = XM_PI / 180.0f;

static const float deltaTime = 0.016667f;

void Initialize()
{
	HRESULT hr = S_OK;

	auto device = Window::Device();

	auto context = Window::Context();

	// 変数初期化

	// シェーダーリソースビュー
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

	// 色
	color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	// 拡散反射光
	diffuseMaterial = Vector4(1.0f, 0.9f, 0.5f, 1.0f);

	// プレイヤー座標
	playerPosition = Vector3(0.0f, 0.0f, 0.0f);
	// プレイヤー回転
	playerRotation = XMMatrixIdentity();

	// エネミー座標
	enemyPosition = Vector3(0.0f, 0.0f, 3.0f);
	// エネミー回転
	enemyRotation = XMMatrixIdentity();

	// プレイヤー
	player = std::make_shared<aqua::Model>(L"Contents/Box.obj");

	// エネミー
	enemy = aqua::Polygon::Plane();

	// テクスチャ
	texture = std::make_shared<aqua::Texture2D>(L"Contents/panda.png");

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
	Shader::SetShaderResource(L"texture2d", shaderResourceView);

	// テクスチャシェーダー
	Shader::AddShader(L"Texture", L"Contents/Shader/TextureShader.hlsl");
	// シェーダーの切り替え
	Shader::Change(L"Texture");
	// テクニックの指定
	Shader::Technique(L"Default");
	// サンプラーステート
	Shader::SetSampler(L"samplerState", 0, sampler);

	// ディフューズ
	Shader::Change(L"Diffuse", L"Contents/Shader/ProgrammableShader.hlsl");
	// テクニック
	Shader::Technique(L"Diffuse");
	// シェーダーリソースビュー
	Shader::SetShaderResource(L"texture2d", shaderResourceView);
	// サンプラーステート
	Shader::SetSampler(L"samplerState", 0, sampler);
	// ディフューズ率
	Shader::SetVector(L"diffuseLight", { 1.0f, 1.0f, 1.0f, 1.0f });
	// ディフューズカラー
	Shader::SetVector(L"diffuseMaterial", diffuseMaterial);
	// ライト座標
	Shader::SetVector(L"lightPosition", { 0.0f, 0.0f, -10.0f, 0.0f });

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

// プレイヤー回転
void PlayerRotate()
{
	float angle = 0.0f;
	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		angle -= oneRadian * deltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		angle += oneRadian * deltaTime;
	}

	playerRotation = playerRotation.RotatedY(angle);
}

// プレイヤー移動
void PlayerMove()
{
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
}

// 敵移動
void EnemyMove()
{
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
	TimeElapsed();

	PlayerRotate();
	PlayerMove();

	EnemyMove();

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

	// 色の変化
	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
	color.w = 1.0f;

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = 1.0f;

	// プレイヤーの描画
	OrderedRender::Regist(color.a, playerPosition.z, [=]
	{
		Shader::Change(L"Default");
		auto model = playerRotation.Translated(playerPosition);
		Shader::SetMatrix(L"modelViewProjection", model * view * projection);
		Shader::SetVector(L"color", color);

		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			player->Render();
		}
	});

	OrderedRender::Regist(diffuseMaterial.a, enemyPosition.z, [=]
	{
		Shader::Change(L"Diffuse");
		auto model = enemyRotation.Translated(enemyPosition);
		auto modelView = model * view;
		Shader::SetMatrix(L"modelView", modelView);
		Shader::SetMatrix(L"modelViewProjection", modelView * projection);
		Shader::SetMatrix(L"normal", modelView.Inverse().Transposed());

		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			enemy->Render();
		}
	});

	OrderedRender::Render();

	Window::Flip();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
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

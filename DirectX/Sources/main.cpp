# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

# include "OrderedRender/OrderedRender.hpp"

# include "Convert/Convert.hpp"

# include "Experimental/TestLoader/TestLoader.hpp"

using namespace DirectX;

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3D11SamplerState> sampler;

Float3 eye;
Float3 at;
Float3 up;

Matrix view;

Matrix projection;

Float4 color;

Matrix playerRotation;
Float3 playerPosition;

Matrix enemyRotation;
Float3 enemyPosition;

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
	eye = Float3(0.0f, 3.0f, -6.0f);

	// 注視点座標
	at = Float3(0.0f, 0.0f, 0.0f);

	// 上方向ベクトル
	up = Float3(0.0f, 1.0f, 0.0f);

	// ビュー行列
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));

	// 透視射影行列
	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, Window::Aspect(), 0.1f, 250.0f);

	// 色
	color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	// プレイヤー座標
	playerPosition = Float3(0.0f, 0.0f, 0.0f);
	// プレイヤー回転
	playerRotation = XMMatrixIdentity();

	// エネミー座標
	enemyPosition = Float3(0.0f, 0.0f, -10.0f);
	// エネミー回転
	enemyRotation = XMMatrixIdentity();

	// プレイヤー
	// player = aqua::Polygon::Box();
	// player = aqua::Polygon::Plane();
	// player = std::make_shared<aqua::Model>(L"Contents/Box.obj");
	player = aqua::Polygon::Box();

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
	// サンプラーステートのセット
	Shader::SetSampler(L"samplerState", 0, sampler);
	// シェーダーリソースビューのセット
	Shader::SetShaderResource(L"texture2d", shaderResourceView);

	// テクスチャシェーダー
	Shader::AddShader(L"Texture", L"Contents/Shader/TextureShader.hlsl");
	// シェーダーの切り替え
	Shader::Change(L"Texture");
	// テクニックの指定
	Shader::Technique(L"Default");
	// サンプラーステートのセット
	Shader::SetSampler(L"samplerState", 0, sampler);

	Shader::Change(L"Diffuse", L"Contents/Shader/ProgrammableShader.hlsl");
	Shader::Technique(L"Diffuse");
	Shader::SetShaderResource(L"texture2d", shaderResourceView);
	Shader::SetSampler(L"samplerState", 0, sampler);
	Shader::SetVector(L"diffuseLight", { 1.0f, 1.0f, 1.0f, 1.0f });
	Shader::SetVector(L"diffuseMaterial", { 1.0f, 0.9f, 0.5f, 1.0f });
	Shader::SetVector(L"lightPosition", { 0.0f, 0.0f, -10.0f, 0.0f });

	Shader::RegistInputLayout();

	Experimental::TestLoader loader { L"Contents/Box.obj" };
	auto v = loader.Vertices();
	auto i = loader.Indices();
};

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
	playerRotation = playerRotation * XMMatrixRotationY(angle);

//	playerRotation = playerRotation * XMMatrixRotationRollPitchYaw(0.0f, oneRadian * deltaTime, 0.0f);
}

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

void ViewMatrix()
{
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));
}

void Update()
{
	TimeElapsed();

	PlayerRotate();
	PlayerMove();

	EnemyMove();

	EyeMove();
	ViewMatrix();
}

void Render()
{
	// 背景色クリア
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	Window::Clear(clearColor);

	// 色の変化
	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
	color.w = 1.0f;

	/*OrderedRender::Regist(1.0f, 0.0f, [=]
	{

		Shader::Change(L"Default");
		Shader::SetMatrix(L"world", XMMatrixScaling(2.0f, 2.0f, 1.0f));
		Shader::SetMatrix(L"view", view);
		Shader::SetMatrix(L"projection", projection);
		Shader::SetVector(L"color", Float4(1.0f, 1.0f, 1.0f, 1.0f));
		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			back->Render();
		}
	});*/

	// プレイヤーの描画
	/*OrderedRender::Regist(0.1f, playerPosition.z, [=]
	{
		Shader::Change(L"Default");
		Shader::SetMatrix(L"world", playerRotation * XMMatrixTranslation(playerPosition.x, playerPosition.y, playerPosition.z));
		Shader::SetMatrix(L"view", view);
		Shader::SetMatrix(L"projection", projection);
		Shader::SetVector(L"color", Float4(1.0f, 1.0f, 1.0f, 0.1f));
		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			player->Render();
		}
	});*/

	OrderedRender::Regist(0.1f, playerPosition.z, [=]
	{
		Shader::Change(L"Diffuse");
		auto model = playerRotation * XMMatrixTranslation(playerPosition.x, playerPosition.y, playerPosition.z);
		auto modelView = model * view;
		Shader::SetMatrix(L"modelView", modelView);
		Shader::SetMatrix(L"modelViewProjection", modelView * projection);
		XMVECTOR det;
		Float4 lightPosition { enemyPosition.x, enemyPosition.y, enemyPosition.z, 0.0f };
		// Shader::SetVector(L"lightPosition", lightPosition);
		auto inverse = XMMatrixInverse(&det, modelView);
		auto transpose = XMMatrixTranspose(inverse);
		Shader::SetMatrix(L"normal", transpose);
		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			player->Render();
		}
	});

	OrderedRender::Regist(1.0f, 0.0f, [=]
	{
		Shader::Change(L"Default");
		for (auto&& pass : Shader::Passes())
		{
			pass.Apply();
			texture->Render();
		}
	});

	// エネミーの描画
	/*OrderedRender::Regist(0.0f, enemyPosition.z, [=]
	{
		Shader::Change(L"Default");
		Shader::SetMatrix(L"world", enemyRotation * XMMatrixTranslation(enemyPosition.x, enemyPosition.y, enemyPosition.z));
		Shader::SetMatrix(L"view", view);
		Shader::SetMatrix(L"projection", projection);
		auto c = color;
		c.a = 0.0f;
		Shader::SetVector(L"color", c);
		for (const auto& pass : Shader::Passes())
		{
			pass.Apply();
			enemy->Render();
		}
	});*/

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
			ToWide(ex.what()).c_str(),
			L"例外をキャッチしました",
			MB_OK);
	}
}

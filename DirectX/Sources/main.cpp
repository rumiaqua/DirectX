# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

// �v���C���[�̃��f��
std::shared_ptr<aqua::Polygon> playerModel;

// �G�l�~�[�̃��f��
std::shared_ptr<aqua::Polygon> enemyModel;

// �e�N�X�`��
std::shared_ptr<aqua::Polygon> texture;

// �v���C���[�̍s��
Matrix playerMatrix;

// �G�l�~�[�̍s��
Matrix enemyMatrix;

// �r���[�s��
Matrix view;

// �����ˉe�s��
Matrix projection;

// �F
Float4 color;

float t;

using namespace DirectX;

void Initialize_()
{
	playerModel = std::make_shared<aqua::Model>(L"Contents/Box.obj");

	enemyModel = aqua::Polygon::Plane();

	texture = std::make_shared<aqua::Texture2D>(L"Contents/panda.png");

	playerMatrix = XMMatrixIdentity();

	enemyMatrix = XMMatrixIdentity();

	view = XMMatrixLookAtLH(
		Float3(0.0f, 3.0f, -6.0f).ToVector(0.0f),
		Float3(0.0f, 0.0f, 0.0f).ToVector(),
		Float3(0.0f, 1.0f, 0.0f).ToVector());

	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, Window::Aspect(), 0.1f, 250.0f);

	color = Float4(1.0f, 0.0f, 0.0f, 1.0f);

	Shader::AddShader(L"Default", L"Contents/Shader/DefaultShader.hlsl");
	Shader::SetSampler(L"samplerState", 0U, )

	Shader::AddShader(L"Texture", L"Contents/Shader/TextureShader.hlsl");
}

void Update_()
{
	// ���Ԃ̌o��
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

	// �ω�����
	static const float deltaTime = 0.016667f;

	// �ړ�
	// player
	Float3 playerVelocity;

	if (GetAsyncKeyState('A') != 0)
	{
		playerVelocity.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('D') != 0)
	{
		playerVelocity.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('W') != 0)
	{
		playerVelocity.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('S') != 0)
	{
		playerVelocity.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('E') != 0)
	{
		playerVelocity.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('X') != 0)
	{
		playerVelocity.y -= 0.1f * deltaTime;
	}

	playerMatrix = playerMatrix * XMMatrixTranslation(
		playerVelocity.x, playerVelocity.y, playerVelocity.z);

	// enemy
	Float3 enemyVelocity;

	if (GetAsyncKeyState('F') != 0)
	{
		enemyVelocity.x -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('H') != 0)
	{
		enemyVelocity.x += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('T') != 0)
	{
		enemyVelocity.z += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('G') != 0)
	{
		enemyVelocity.z -= 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('Y') != 0)
	{
		enemyVelocity.y += 0.1f * deltaTime;
	}

	if (GetAsyncKeyState('B') != 0)
	{
		enemyVelocity.y -= 0.1f * deltaTime;
	}

	enemyMatrix = enemyMatrix * XMMatrixTranslation(
		enemyVelocity.x, enemyVelocity.y, enemyVelocity.z);
}

void Render_()
{
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	Window::Clear(clearColor);

	// �F�ω�
	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
	color.w = 1.0f;
	Shader::Change(L"");
	Shader::SetVector(L"vMeshColor", color);

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

	player->Render();

	// enemy render
	Shader::Change(L"Default");
	Shader::SetMatrix(L"World", XMMatrixTranslation(enemyPosition.x, enemyPosition.y, enemyPosition.z));
	Shader::SetMatrix(L"View", view);
	Shader::SetMatrix(L"Projection", projection);
	Shader::SetVector(L"vMeshColor", color);
	Shader::Apply();

	enemy->Render();

	// texture render
	texture->Render();

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

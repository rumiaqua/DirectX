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

	// �ϐ�������

	// �V�F�[�_�[���\�[�X�r���[
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

	// �T���v���[�X�e�[�g
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

	// ���_���W
	eye = Vector3(0.0f, 3.0f, -6.0f);

	// �����_���W
	at = Vector3(0.0f, 0.0f, 0.0f);

	// ������x�N�g��
	up = Vector3(0.0f, 1.0f, 0.0f);

	// �r���[�s��
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));

	// �����ˉe�s��
	projection = XMMatrixPerspectiveFovLH(
		XM_PIDIV4, Window::Aspect(), 0.1f, 250.0f);

	// �F
	color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	// �g�U���ˌ�
	diffuseMaterial = Vector4(1.0f, 0.9f, 0.5f, 1.0f);

	// �v���C���[���W
	playerPosition = Vector3(0.0f, 0.0f, 0.0f);
	// �v���C���[��]
	playerRotation = XMMatrixIdentity();

	// �G�l�~�[���W
	enemyPosition = Vector3(0.0f, 0.0f, 3.0f);
	// �G�l�~�[��]
	enemyRotation = XMMatrixIdentity();

	// �v���C���[
	player = std::make_shared<aqua::Model>(L"Contents/Box.obj");

	// �G�l�~�[
	enemy = aqua::Polygon::Plane();

	// �e�N�X�`��
	texture = std::make_shared<aqua::Texture2D>(L"Contents/panda.png");

	// �V�F�[�_�[�̃Z�b�g

	// �f�t�H���g�V�F�[�_�[
	Shader::AddShader(L"Default", L"Contents/Shader/DefaultShader.hlsl");
	// �V�F�[�_�[�̐؂�ւ�
	Shader::Change(L"Default");
	// �e�N�j�b�N�̎w��
	Shader::Technique(L"Default");
	// �T���v���[�X�e�[�g
	Shader::SetSampler(L"samplerState", 0, sampler);
	// �V�F�[�_�[���\�[�X�r���[
	Shader::SetShaderResource(L"texture2d", shaderResourceView);

	// �e�N�X�`���V�F�[�_�[
	Shader::AddShader(L"Texture", L"Contents/Shader/TextureShader.hlsl");
	// �V�F�[�_�[�̐؂�ւ�
	Shader::Change(L"Texture");
	// �e�N�j�b�N�̎w��
	Shader::Technique(L"Default");
	// �T���v���[�X�e�[�g
	Shader::SetSampler(L"samplerState", 0, sampler);

	// �f�B�t���[�Y
	Shader::Change(L"Diffuse", L"Contents/Shader/ProgrammableShader.hlsl");
	// �e�N�j�b�N
	Shader::Technique(L"Diffuse");
	// �V�F�[�_�[���\�[�X�r���[
	Shader::SetShaderResource(L"texture2d", shaderResourceView);
	// �T���v���[�X�e�[�g
	Shader::SetSampler(L"samplerState", 0, sampler);
	// �f�B�t���[�Y��
	Shader::SetVector(L"diffuseLight", { 1.0f, 1.0f, 1.0f, 1.0f });
	// �f�B�t���[�Y�J���[
	Shader::SetVector(L"diffuseMaterial", diffuseMaterial);
	// ���C�g���W
	Shader::SetVector(L"lightPosition", { 0.0f, 0.0f, -10.0f, 0.0f });

	// ���̓��C�A�E�g�̓o�^
	Shader::RegistInputLayout();
};

// ���Ԍo��
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

// �v���C���[��]
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

// �v���C���[�ړ�
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

// �G�ړ�
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

// ���_�ړ�
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

// �r���[�s��̍X�V
void ViewMatrix()
{
	view = XMMatrixLookAtLH(
		eye.ToVector(0.0f),
		at.ToVector(0.0f),
		up.ToVector(0.0f));
}

// �X�V
void Update()
{
	TimeElapsed();

	PlayerRotate();
	PlayerMove();

	EnemyMove();

	EyeMove();
	ViewMatrix();
}

// �`��
void Render()
{
	// �w�i�F�N���A
	static float clearColor[] =
	{
		0.1f, 0.1f, 0.5f, 1.0f,
	};
	Window::Clear(clearColor);

	// �F�̕ω�
	color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
	color.w = 1.0f;

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = 1.0f;

	// �v���C���[�̕`��
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
			L"��O���L���b�`���܂���",
			MB_OK);
	}
}

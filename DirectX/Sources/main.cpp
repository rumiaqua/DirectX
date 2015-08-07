# include "Window/Window.hpp"

# include "Model/Model.hpp"

# include "Shader/Shader.hpp"

# include "Texture2D/Texture2D.hpp"

# include "OrderedRender/OrderedRender.hpp"

# include "Convert/Convert.hpp"

# include "RenderObject/RenderPlayer.hpp"

# include "RenderObject/RenderEnemy.hpp"


using namespace aqua;

using namespace DirectX;

Handle<ID3D11ShaderResourceView> shaderResourceView;

Handle<ID3D11SamplerState> sampler;

Vector3 eye;
Vector3 at;
Vector3 up;

Matrix view;

Matrix projection;

static float t = 0.0f;

static const float deltaTime = 0.016667f;

RenderPlayer player(view, projection);

RenderPlayer enemy(view, projection);

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
	Shader::SetVector(L"diffuseMaterial", { 1.0f, 0.9f, 0.5f, 0.7f });
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

	player.Update();
	enemy.Update();

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

	player.Render();
	enemy.Render();

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
